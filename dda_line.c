#include <raylib.h>
#include <math.h>
#include <stdio.h>

// Screen dimensions
const int screenWidth = 800;
const int screenHeight = 600;

int originX = screenWidth / 2;
int originY = screenHeight / 2;

// Function to convert Cartesian to screen coordinates and draw a pixel
void DrawPixelCartesian(int x, int y, Color color) {
    DrawPixel(originX + x, originY - y, color);
}

// Draw X and Y axes
void DrawAxes() {
    DrawLine(0, originY, screenWidth, originY, GRAY);   // X-axis
    DrawLine(originX, 0, originX, screenHeight, GRAY);  // Y-axis
}

// DDA algorithm to draw line in Cartesian space
void DDA(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    float xi = dx / steps;
    float yi = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        DrawPixelCartesian((int)roundf(x), (int)roundf(y), WHITE);
        x += xi;
        y += yi;

        // Render and delay for visual effect
        EndDrawing();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawAxes();
        DrawPixelCartesian((int)roundf(x), (int)roundf(y), RED); // Optional cursor pixel
        for (int j = 0; j <= i; j++) {
            float xt = x1 + j * xi;
            float yt = y1 + j * yi;
            DrawPixelCartesian((int)roundf(xt), (int)roundf(yt), WHITE);
        }
        DrawFPS(10, 10);
        WaitTime(0.01); // ~10ms delay
    }
}

int main() {
    // Initialize window
    InitWindow(screenWidth, screenHeight, "DDA Line Drawing - Raylib Cartesian");
    SetTargetFPS(60);

    int x1, y1, x2, y2;

    // Get coordinates from user
    printf("Enter coordinates of first point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter coordinates of second point (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    BeginDrawing();
    ClearBackground(BLACK);
    DrawAxes();
    EndDrawing();

    // Draw the line with DDA
    BeginDrawing();
    ClearBackground(BLACK);
    DrawAxes();
    DDA(x1, y1, x2, y2);
    EndDrawing();

    // Wait until user closes the window
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawAxes();
        DDA(x1, y1, x2, y2);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
