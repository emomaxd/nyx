#pragma once

#include "raylib.h"
#include "Rope/Rope.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float TIMESTEP = 0.066f; // 60 FPS

void SimulateRope()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rope Simulation");
    SetTargetFPS(60);

    Rope rope;
    glm::vec3 start(400, 400, 0);
    float segmentLength = 20.0f;
    int particleCount = 20;

    for (int i = 0; i < particleCount; ++i) {
        glm::vec3 position = start + glm::vec3(i * segmentLength, 0, 0);
        bool isFixed = (i == 0);
        rope.AddParticle(position, 1.0f, isFixed);

        if (i > 0) {
            rope.AddConstraint(i - 1, i);
        }
    }

    while (!WindowShouldClose())
    {
        rope.Update(TIMESTEP);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        const auto& particles = rope.GetParticles();
        for (size_t i = 0; i < particles.size() - 1; ++i) {
            DrawLine(
                particles[i].position.x,
                SCREEN_HEIGHT - particles[i].position.y,
                particles[i + 1].position.x,
                SCREEN_HEIGHT - particles[i + 1].position.y,
                DARKGRAY
            );
        }

        for (const auto& particle : particles) {
            DrawCircleV(
                { particle.position.x, SCREEN_HEIGHT - particle.position.y },
                4, particle.isFixed ? BLUE : RED
            );
        }

        EndDrawing();
    }

    CloseWindow();
}


void SimulateCloth()
{

}