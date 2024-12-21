#pragma once


#include <vector>
#include <random>

#include <cuda_runtime.h>

#include "Timestep.h"
#include "Vector.h"

class NBodySimulation {
public:
    NBodySimulation(size_t num_Particles);
    ~NBodySimulation();

    void update(Timestep ts);
    inline const std::vector<float3>& getPositions() const { return h_Positions; } // For visualization
    inline const std::vector<float3>& getVelocities() const { return h_Velocities; }
    inline const std::vector<float>& getMasses() const { return h_Masses; }
    inline const std::vector<float>& getRadiuses() const { return h_Radii; }
    inline const std::vector<float>& getDensities() const { return h_Densities; }

private:
    
    float3* d_Positions;
    float3* d_Velocities;
    float3* d_Accelerations;
    float* d_Masses;
    float* d_Radii;
    float* d_Densities;

    
    std::vector<float3> h_Positions;
    std::vector<float3> h_Velocities;
    std::vector<float3> h_Accelerations;
    std::vector<float> h_Masses;        
    std::vector<float> h_Radii;         
    std::vector<float> h_Densities;     

    size_t num_Particles;


private:
    cudaError_t checkCuda(cudaError_t result);

    void initializeParticles();

    void transferDataToDevice();
    void transferDataToHost();
};

__global__ void nBodyKernel(float3* d_Positions, float3* d_Velocities, float3* d_Accelerations,
                             float* d_Masses, float* d_Radii, float* d_Densities,
                             uint32_t num_Particles, float dt);