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

void DrawCirclePoints(int xc, int yc, int x, int y, Color color)
{
    DrawPixel(toScreenX(xc + x), toScreenY(yc + y), color);
    DrawPixel(toScreenX(xc - x), toScreenY(yc + y), color);
    DrawPixel(toScreenX(xc + x), toScreenY(yc - y), color);
    DrawPixel(toScreenX(xc - x), toScreenY(yc - y), color);
    DrawPixel(toScreenX(xc + y), toScreenY(yc + x), color);
    DrawPixel(toScreenX(xc - y), toScreenY(yc + x), color);
    DrawPixel(toScreenX(xc + y), toScreenY(yc - x), color);
    DrawPixel(toScreenX(xc - y), toScreenY(yc - x), color);
}

void DrawCircleMidpoint(int xc, int yc, int r, Color color)
{
    int x = 0;
    int y = r;
    int p = 1 - r;

    DrawCirclePoints(xc, yc, x, y, color);

    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        DrawCirclePoints(xc, yc, x, y, color);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Midpoint Circle Algorithm - Origin at Center");
    SetTargetFPS(60);

    int xc, yc, r;

    printf("Enter center (xc yc) relative to center of screen (0, 0): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter radius r: ");
    scanf("%d", &r);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GRAY); // x-axis
        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GRAY);  // y-axis

        DrawCircleMidpoint(xc, yc, r, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
