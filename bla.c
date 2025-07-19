#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int originX, originY;

// Draw pixel in Cartesian coordinates (origin at center)
void DrawPixelCartesian(int x, int y, Color color)
{
    DrawPixel(originX + x, originY - y, color);
}

// Draw Cartesian axes
void DrawAxes()
{
    DrawLine(0, originY, SCREEN_WIDTH, originY, GRAY);  // X-axis
    DrawLine(originX, 0, originX, SCREEN_HEIGHT, GRAY); // Y-axis
}

// Draw line using Bresenham algorithm and print coordinates once
void DrawLineBresenham(int x1, int y1, int x2, int y2, Color color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int incx = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
    int incy = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);

    dx = abs(dx);
    dy = abs(dy);

    int x = x1;
    int y = y1;
    int p;

    if (dx > dy)
    {
        p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            DrawPixelCartesian(x, y, color);
            printf("(%d, %d)\n", x, y);
            x += incx;
            if (p < 0)
            {
                p += 2 * dy;
            }
            else
            {
                y += incy;
                p += 2 * (dy - dx);
            }
        }
    }
    else
    {
        p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++)
        {
            DrawPixelCartesian(x, y, color);
            printf("(%d, %d)\n", x, y);
            y += incy;
            if (p < 0)
            {
                p += 2 * dx;
            }
            else
            {
                x += incx;
                p += 2 * (dx - dy);
            }
        }
    }

    fflush(stdout); // Ensure all output is flushed
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Bresenham Line with Input");
    SetTargetFPS(60);

    originX = SCREEN_WIDTH / 2;
    originY = SCREEN_HEIGHT / 2;

    int x1, y1, x2, y2;

    // Input from user
    printf("Enter starting point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter ending point (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    // Draw the line and print points only ONCE
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Bresenham Line - Press ESC to Exit", 10, 10, 20, DARKGRAY);
    DrawAxes();
    DrawLineBresenham(x1, y1, x2, y2, BLACK); // this is now called only once
    EndDrawing();

    // Wait until user closes the window
    while (!WindowShouldClose())
    {
        // No redraw needed, just keep window open
    }

    CloseWindow();
    return 0;
}
