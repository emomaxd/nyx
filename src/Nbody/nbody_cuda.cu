#include "nbody_cuda.cuh"
#include <iostream>
#include <cmath>

NBodySimulation::NBodySimulation(size_t num_Particles)
    : num_Particles(num_Particles)
{
    h_Positions.resize(num_Particles);
    h_Velocities.resize(num_Particles);
    h_Accelerations.resize(num_Particles);
    h_Masses.resize(num_Particles);
    h_Radii.resize(num_Particles);
    h_Densities.resize(num_Particles);

    cudaMalloc(&d_Positions, num_Particles * sizeof(float3));
    cudaMalloc(&d_Velocities, num_Particles * sizeof(float3));
    cudaMalloc(&d_Accelerations, num_Particles * sizeof(float3));
    cudaMalloc(&d_Masses, num_Particles * sizeof(float));
    cudaMalloc(&d_Radii, num_Particles * sizeof(float));
    cudaMalloc(&d_Densities, num_Particles * sizeof(float));

    initializeParticles();
    transferDataToDevice();
}

NBodySimulation::~NBodySimulation() {
    cudaFree(d_Positions);
    cudaFree(d_Velocities);
    cudaFree(d_Accelerations);
    cudaFree(d_Masses);
    cudaFree(d_Radii);
    cudaFree(d_Densities);
}

void NBodySimulation::initializeParticles() {
    std::mt19937 gen(static_cast<unsigned>(time(nullptr)));
    std::uniform_real_distribution<float> posDistX(20.0f, 1400.0f);
    std::uniform_real_distribution<float> posDistY(10.0f, 900.0f);
    std::uniform_real_distribution<float> posDistZ(-10000.0f, 10000.0f);
    std::uniform_real_distribution<float> massDist(1.0f, 1e7f);
    std::uniform_real_distribution<float> radiusDist(0.1f, 5.0f);

    for (uint32_t i = 0; i < num_Particles; ++i) {
        h_Positions[i] = make_float3(posDistX(gen), posDistY(gen), posDistZ(gen));
        h_Velocities[i] = make_float3(0.0f, 0.0f, 0.0f);
        h_Accelerations[i] = make_float3(0.0f, 0.0f, 0.0f);
        h_Masses[i] = massDist(gen);
        h_Radii[i] = radiusDist(gen);
        h_Densities[i] = h_Masses[i] / (4.0f / 3.0f * M_PI * std::pow(h_Radii[i], 3));
    }
}

void NBodySimulation::transferDataToDevice() {
    cudaMemcpy(d_Positions, h_Positions.data(), num_Particles * sizeof(float3), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Velocities, h_Velocities.data(), num_Particles * sizeof(float3), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Accelerations, h_Accelerations.data(), num_Particles * sizeof(float3), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Masses, h_Masses.data(), num_Particles * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Radii, h_Radii.data(), num_Particles * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Densities, h_Densities.data(), num_Particles * sizeof(float), cudaMemcpyHostToDevice);
}

void NBodySimulation::transferDataToHost() {
    cudaMemcpy(h_Positions.data(), d_Positions, num_Particles * sizeof(float3), cudaMemcpyDeviceToHost);
    cudaMemcpy(h_Velocities.data(), d_Velocities, num_Particles * sizeof(float3), cudaMemcpyDeviceToHost);
    cudaMemcpy(h_Accelerations.data(), d_Accelerations, num_Particles * sizeof(float3), cudaMemcpyDeviceToHost);
}

void NBodySimulation::update(Timestep ts) {

    int threadsPerBlock = 256;
    int blocks = (num_Particles + threadsPerBlock - 1) / threadsPerBlock;

    nBodyKernel<<<blocks, threadsPerBlock>>>(d_Positions, d_Velocities, d_Accelerations,
                                             d_Masses, d_Radii, d_Densities,
                                             num_Particles, ts);

    cudaDeviceSynchronize();

    transferDataToHost();
}

cudaError_t NBodySimulation::checkCuda(cudaError_t result) {
    if (result != cudaSuccess) {
        std::cerr << "CUDA Runtime Error: " << cudaGetErrorString(result) << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return result;
}

__global__ void nBodyKernel(float3* d_Positions, float3* d_Velocities, float3* d_Accelerations,
                             float* d_Masses, float* d_Radii, float* d_Densities,
                             uint32_t num_Particles, float dt) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= num_Particles) return;

    const float G = 6.67408f * 1e-11f;
    const float maxSpeed = 2000.0f; // Maximum allowed speed

    float3 position = d_Positions[idx];
    float3 velocity = d_Velocities[idx];
    float3 acceleration = make_float3(0.0f, 0.0f, 0.0f);

    // Compute gravitational forces
    for (uint32_t i = 0; i < num_Particles; ++i) {
        if (i == idx) continue;

        float3 otherPosition = d_Positions[i];
        float3 direction = make_float3(otherPosition.x - position.x,
                                       otherPosition.y - position.y,
                                       otherPosition.z - position.z);

        float distSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
        float dist = sqrtf(distSq + 1e-7f); // Avoid division by zero
        float force = G * (d_Masses[i] * d_Masses[idx]) / (distSq + 1e-7f);

        direction.x /= dist;
        direction.y /= dist;
        direction.z /= dist;

        acceleration.x += force * direction.x;
        acceleration.y += force * direction.y;
        acceleration.z += force * direction.z;
    }

    // Update velocities and positions
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    velocity.z += acceleration.z * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    // Clamp positions to bounds
    position.x = fminf(fmaxf(position.x, 0.0f), 1600.0f);
    position.y = fminf(fmaxf(position.y, 0.0f), 900.0f);
    position.z = fminf(fmaxf(position.z, -10000.0f), 10000.0f);

    // Limit speed to maxSpeed
    float speedSq = velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z;
    if (speedSq > maxSpeed * maxSpeed) {
        float scale = maxSpeed / sqrtf(speedSq);
        velocity.x *= scale;
        velocity.y *= scale;
        velocity.z *= scale;
    }

    // Write back updated values
    d_Positions[idx] = position;
    d_Velocities[idx] = velocity;
    d_Accelerations[idx] = acceleration; // Update acceleration for the next step
}

