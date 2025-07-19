#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PI 3.14159f
#define CYAN (Color){ 0, 255, 255, 255 }

typedef struct Point {
    float x, y;
} Point;

int toScreenX(float x) {
    return SCREEN_WIDTH / 2 + (int)x;
}

int toScreenY(float y) {
    return SCREEN_HEIGHT / 2 - (int)y;
}

void drawAxes() {
    DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, DARKGRAY); // X-axis
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, DARKGRAY);  // Y-axis
}

void drawTriangle(Point p1, Point p2, Point p3, Color color) {
    DrawLine(toScreenX(p1.x), toScreenY(p1.y), toScreenX(p2.x), toScreenY(p2.y), color);
    DrawLine(toScreenX(p2.x), toScreenY(p2.y), toScreenX(p3.x), toScreenY(p3.y), color);
    DrawLine(toScreenX(p3.x), toScreenY(p3.y), toScreenX(p1.x), toScreenY(p1.y), color);
}

void drawPoint(Point p, Color color) {
    DrawCircle(toScreenX(p.x), toScreenY(p.y), 4, color);
}

void translate(Point *p, float dx, float dy) {
    p->x += dx;
    p->y += dy;
}

void rotateOrigin(Point *p, float angle) {
    angle = angle * PI / 180.0f;
    float x = p->x;
    float y = p->y;
    p->x = x * cosf(angle) - y * sinf(angle);
    p->y = x * sinf(angle) + y * cosf(angle);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Triangle Rotation Around Fixed Point");
    SetTargetFPS(60);

    Point p1, p2, p3, fixed;
    float angle;

    printf("Enter triangle vertices (x1 y1 x2 y2 x3 y3): ");
    scanf("%f %f %f %f %f %f", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

    printf("Enter fixed point for rotation (xf yf): ");
    scanf("%f %f", &fixed.x, &fixed.y);

    printf("Enter angle of rotation: ");
    scanf("%f", &angle);

    // Step 1: Translate to origin
    Point p1_t = p1, p2_t = p2, p3_t = p3;
    translate(&p1_t, -fixed.x, -fixed.y);
    translate(&p2_t, -fixed.x, -fixed.y);
    translate(&p3_t, -fixed.x, -fixed.y);

    // Step 2: Rotate
    Point p1_r = p1_t, p2_r = p2_t, p3_r = p3_t;
    rotateOrigin(&p1_r, angle);
    rotateOrigin(&p2_r, angle);
    rotateOrigin(&p3_r, angle);

    // Step 3: Translate back
    Point p1_f = p1_r, p2_f = p2_r, p3_f = p3_r;
    translate(&p1_f, fixed.x, fixed.y);
    translate(&p2_f, fixed.x, fixed.y);
    translate(&p3_f, fixed.x, fixed.y);

    int step = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        drawAxes();

        drawPoint(fixed, RED);

        if (step == 0) {
            DrawText("Step 1: Original + Translated to origin", 10, 10, 20, WHITE);
            drawTriangle(p1, p2, p3, WHITE);
            drawTriangle(p1_t, p2_t, p3_t, CYAN);
        } else if (step == 1) {
            DrawText("Step 2: Rotated around origin", 10, 10, 20, WHITE);
            drawTriangle(p1_r, p2_r, p3_r, GREEN);
        } else if (step == 2) {
            DrawText("Step 3: Translated back to fixed point", 10, 10, 20, WHITE);
            drawTriangle(p1_f, p2_f, p3_f, YELLOW);
        }

        DrawText("Press [SPACE] to continue, [ESC] to quit", 10, 40, 20, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            step = (step + 1) % 3;
        }
    }

    CloseWindow();
    return 0;
}
