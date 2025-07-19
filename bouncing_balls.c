#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // for sqrtf()

#define MAX_BALLS 20

typedef struct Ball
{
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
} Ball;

Ball balls[MAX_BALLS];

// Manual Vector2Distance function (if your raylib lacks it)
float Vector2Distance(Vector2 v1, Vector2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrtf(dx * dx + dy * dy);
}

// Clamp function to limit speed values
float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

void InitBalls(int count, int screenWidth, int screenHeight)
{
    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        balls[i].radius = 15 + rand() % 20;
        balls[i].position = (Vector2){
            (float)(rand() % (screenWidth - (int)(2 * balls[i].radius)) + balls[i].radius),
            (float)(rand() % (screenHeight - (int)(2 * balls[i].radius)) + balls[i].radius)};
        // Increased initial speed: divide by 30 instead of 60 to double speed
        balls[i].speed = (Vector2){(float)(rand() % 200 - 100) / 30.0f, (float)(rand() % 200 - 100) / 30.0f};
        balls[i].color = (Color){(unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), 255};
    }
}

void UpdateBall(Ball *ball, int screenWidth, int screenHeight)
{
    ball->position.x += ball->speed.x;
    ball->position.y += ball->speed.y;

    // Bounce on walls
    if ((ball->position.x + ball->radius) >= screenWidth)
    {
        ball->position.x = screenWidth - ball->radius;
        ball->speed.x *= -1;
    }
    else if ((ball->position.x - ball->radius) <= 0)
    {
        ball->position.x = ball->radius;
        ball->speed.x *= -1;
    }
    if ((ball->position.y + ball->radius) >= screenHeight)
    {
        ball->position.y = screenHeight - ball->radius;
        ball->speed.y *= -1;
    }
    else if ((ball->position.y - ball->radius) <= 0)
    {
        ball->position.y = ball->radius;
        ball->speed.y *= -1;
    }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Bouncing Balls - Speed Control");
    SetTargetFPS(60);

    int ballCount = 10;
    InitBalls(ballCount, screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        // Increase horizontal speed (Right arrow) by 10%
        if (IsKeyDown(KEY_RIGHT))
        {
            for (int i = 0; i < ballCount; i++)
                balls[i].speed.x *= 1.1f;
        }
        // Decrease horizontal speed (Left arrow) by 10%
        if (IsKeyDown(KEY_LEFT))
        {
            for (int i = 0; i < ballCount; i++)
                balls[i].speed.x *= 0.9f;
        }
        // Increase vertical speed (Down arrow) by 10%
        if (IsKeyDown(KEY_DOWN))
        {
            for (int i = 0; i < ballCount; i++)
                balls[i].speed.y *= 1.1f;
        }
        // Decrease vertical speed (Up arrow) by 10%
        if (IsKeyDown(KEY_UP))
        {
            for (int i = 0; i < ballCount; i++)
                balls[i].speed.y *= 0.9f;
        }

        // Clamp speeds so they don't get too high or too low
        for (int i = 0; i < ballCount; i++)
        {
            balls[i].speed.x = clamp(balls[i].speed.x, -5.0f, 5.0f);
            balls[i].speed.y = clamp(balls[i].speed.y, -5.0f, 5.0f);
        }

        // Change ball color on mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            for (int i = 0; i < ballCount; i++)
            {
                float dist = Vector2Distance(mousePos, balls[i].position);
                if (dist <= balls[i].radius)
                {
                    balls[i].color = (Color){(unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), 255};
                }
            }
        }

        // Update all balls positions
        for (int i = 0; i < ballCount; i++)
        {
            UpdateBall(&balls[i], screenWidth, screenHeight);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Arrow keys to increase/decrease ball speed", 10, 10, 20, DARKGRAY);
        DrawText("Click a ball to change its color", 10, 40, 20, DARKGRAY);

        for (int i = 0; i < ballCount; i++)
        {
            DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
