#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int toScreenX(int x)
{
    return SCREEN_WIDTH / 2 + x;
}

int toScreenY(int y)
{
    return SCREEN_HEIGHT / 2 - y;
}

void DrawEllipsePoints(int xc, int yc, int x, int y, Color color)
{
    DrawPixel(toScreenX(xc + x), toScreenY(yc + y), color);
    DrawPixel(toScreenX(xc - x), toScreenY(yc + y), color);
    DrawPixel(toScreenX(xc + x), toScreenY(yc - y), color);
    DrawPixel(toScreenX(xc - x), toScreenY(yc - y), color);
}

// Midpoint ellipse drawing algorithm
void DrawEllipseMidpoint(int xc, int yc, int a, int b, Color color)
{
    float x = 0;
    float y = b;

    float a2 = a * a;
    float b2 = b * b;

    float d1 = b2 - a2 * b + 0.25f * a2;
    float dx = 2 * b2 * x;
    float dy = 2 * a2 * y;

    // Region 1
    while (dx < dy)
    {
        DrawEllipsePoints(xc, yc, (int)x, (int)y, color);
        if (d1 < 0)
        {
            x++;
            dx += 2 * b2;
            d1 += dx + b2;
        }
        else
        {
            x++;
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d1 += dx - dy + b2;
        }
    }

    // Region 2
    float d2 = b2 * (x + 0.5f) * (x + 0.5f) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y >= 0)
    {
        DrawEllipsePoints(xc, yc, (int)x, (int)y, color);
        if (d2 > 0)
        {
            y--;
            dy -= 2 * a2;
            d2 += a2 - dy;
        }
        else
        {
            y--;
            x++;
            dx += 2 * b2;
            dy -= 2 * a2;
            d2 += dx - dy + a2;
        }
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Midpoint Ellipse Algorithm - Origin at Center");
    SetTargetFPS(60);

    int xc, yc, a, b;

    printf("Enter ellipse center (xc yc) relative to center of screen (0, 0): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter semi-major axis (a): ");
    scanf("%d", &a);
    printf("Enter semi-minor axis (b): ");
    scanf("%d", &b);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GRAY); // x-axis
        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GRAY);  // y-axis

        DrawEllipseMidpoint(xc, yc, a, b, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
