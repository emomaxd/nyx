#include "Rope.h"

void Rope::AddParticle(const glm::vec3& position, float mass, bool isFixed)
{
    particles.emplace_back(position, mass, isFixed);
}

void Rope::AddConstraint(int p1, int p2)
{
    float restLength = glm::length(particles[p2].position - particles[p1].position);
    constraints.emplace_back(p1, p2, restLength);
}

void Rope::ApplyForces(float timestep)
{
    for (auto& particle : particles) {
        if (particle.isFixed) continue;

        glm::vec3 acceleration(0.0f, -GRAVITY, 0.0f);
        particle.position += acceleration * timestep * timestep;
    }
}

void Rope::Integrate()
{
    for (auto& particle : particles)
    {
        if (particle.isFixed) continue;

        glm::vec3 tempPosition = particle.position;

        particle.position += (particle.position - particle.oldPosition);

        particle.oldPosition = tempPosition;
    }
}

void Rope::SatisfyConstraints()
{
    for (int i = 0; i < CONSTRAINT_ITERATIONS; ++i) {
        for (const auto& constraint : constraints) {
            Particle& p1 = particles[constraint.p1];
            Particle& p2 = particles[constraint.p2];

            glm::vec3 delta = p2.position - p1.position;
            float current_length = glm::length(delta);
            float correction = (current_length - constraint.restLength) / current_length;

            if (!p1.isFixed) {
                p1.position += delta * correction * 0.5f;
            }
            if (!p2.isFixed) {
                p2.position -= delta * correction * 0.5f;
            }
        }
    }
}

void Rope::Update(float timestep)
{
    ApplyForces(timestep);
    Integrate();
    SatisfyConstraints();
}

const std::vector<Particle>& Rope::GetParticles() const
{
    return particles;
}
