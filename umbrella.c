#include "raylib.h"
#include <math.h>

#define DEG2RAD (PI / 180.0f)

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "umbrella");
    SetTargetFPS(60);

    int centerX = screenWidth / 2;
    int centerY = 250;
    int umbrellaRadius = 120;
    int numStripes = 8;

    Color stripeColors[8] = {
        RED, ORANGE, YELLOW, GREEN,
        BLUE, PURPLE, PINK, MAROON};

    int stickWidth = 4;
    int stickHeight = 160;
    float hookRadius = 25.0f;
    int hookSegments = 40;
    float hookThickness = 4.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw umbrella stripes (smooth curved sectors)
        float anglePerStripe = 180.0f / numStripes;
        for (int i = 0; i < numStripes; i++)
        {
            float startAngle = 180 + i * anglePerStripe;
            float endAngle = startAngle + anglePerStripe;

            DrawCircleSector(
                (Vector2){centerX, centerY},
                umbrellaRadius,
                startAngle,
                endAngle,
                100,
                stripeColors[i % 8]);
        }

        // ✅ Lowered dot at top of umbrella (was -10, now -5)
        DrawCircle(centerX, centerY - umbrellaRadius - 5, 8, DARKGRAY);

        // Draw umbrella stick (rectangle below center)
        int stickTopY = centerY;
        int stickBottomY = stickTopY + stickHeight;
        DrawRectangle(centerX - stickWidth / 2, stickTopY, stickWidth, stickHeight, DARKGRAY);

        // Draw J-shaped curved handle (hook)
        float hookCenterX = centerX + hookRadius;
        float hookCenterY = stickBottomY;

        for (int i = 0; i < hookSegments; i++)
        {
            float theta1 = PI - (i * PI / hookSegments);     // 180 to 0 degrees
            float theta2 = PI - ((i + 1) * PI / hookSegments);

            Vector2 p1 = {
                hookCenterX + hookRadius * cosf(theta1),
                hookCenterY + hookRadius * sinf(theta1)};
            Vector2 p2 = {
                hookCenterX + hookRadius * cosf(theta2),
                hookCenterY + hookRadius * sinf(theta2)};

            DrawLineEx(p1, p2, hookThickness, DARKGRAY);
        }

        // Title
        DrawText("Perfect Colorful Umbrella", 10, 10, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
