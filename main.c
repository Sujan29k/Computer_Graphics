#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PARTICLES 200

typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float life;  // life remaining in seconds
} Particle;

Particle particles[MAX_PARTICLES];

void InitParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position = (Vector2){-100, -100};  // off-screen initially
        particles[i].velocity = (Vector2){0, 0};
        particles[i].color = WHITE;
        particles[i].size = 0;
        particles[i].life = 0;
    }
}

void SpawnParticle(float x, float y) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life <= 0) {
            particles[i].position = (Vector2){x, y};
            float angle = (float)(rand() % 360) * (PI / 180.0f);
            float speed = (float)(rand() % 50) / 10.0f + 1.0f;
            particles[i].velocity = (Vector2){cosf(angle) * speed, sinf(angle) * speed};
            particles[i].color = (Color){ rand() % 256, rand() % 256, rand() % 256, 255 };
            particles[i].size = (float)(rand() % 5) + 2;
            particles[i].life = 2.0f; // 2 seconds life
            break;
        }
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Interactive Particle System - Raylib");
    SetTargetFPS(60);

    InitParticles();

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // Spawn particles when mouse button pressed
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < 5; i++) {
                SpawnParticle(mousePos.x, mousePos.y);
            }
        }

        // Update particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (particles[i].life > 0) {
                particles[i].life -= GetFrameTime();
                particles[i].position.x += particles[i].velocity.x;
                particles[i].position.y += particles[i].velocity.y;
                particles[i].velocity.y += 0.1f; // gravity effect
                particles[i].size *= 0.98f;       // shrink over time
                if (particles[i].size < 0.1f) particles[i].size = 0;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Hold left mouse button to spawn particles", 10, 10, 20, LIGHTGRAY);

        // Draw particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (particles[i].life > 0 && particles[i].size > 0) {
                DrawCircleV(particles[i].position, particles[i].size, particles[i].color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}


