#pragma once

#include <glm/glm.hpp>
#include <vector>

const float GRAVITY = 9.81f;
const uint32_t CONSTRAINT_ITERATIONS = 5;

struct Particle 
{
    glm::vec3 position;
    glm::vec3 oldPosition;
    float mass;
    bool isFixed;

    Particle(glm::vec3 pos, float mass, bool isFixed = false)
        : position(pos), oldPosition(pos), mass(mass), isFixed(isFixed) {}
};

struct Constraint
{
    uint32_t p1, p2;
    float restLength;

    Constraint(int p1, int p2, float restLength)
        : p1(p1), p2(p2), restLength(restLength) {}
};

class Rope
{
public:
    void AddParticle(const glm::vec3& position, float mass, bool isFixed = false);
    void AddConstraint(int p1, int p2);
    void Update(float timestep);

    const std::vector<Particle>& GetParticles() const;

private:
    void ApplyForces(float timestep);
    void Integrate();
    void SatisfyConstraints();

private:
    std::vector<Particle> particles;
    std::vector<Constraint> constraints;
};
