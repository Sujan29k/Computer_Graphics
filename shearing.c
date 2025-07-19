#include "raylib.h"
#include <stdio.h>

// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Define custom colors
#define CYAN (Color){ 0, 255, 255, 255 }

typedef struct Point {
    float x, y;
} Point;

// Convert Cartesian to screen coordinates
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

// Shear with respect to X-axis
void shearX(Point *p, float shx) {
    p->x = p->x + shx * p->y;
}

// Shear with respect to Y-axis
void shearY(Point *p, float shy) {
    p->y = p->y + shy * p->x;
}

// Combined X and Y shearing
void shearXY(Point *p, float shx, float shy) {
    float newX = p->x + shx * p->y;
    float newY = p->y + shy * p->x;
    p->x = newX;
    p->y = newY;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Triangle Shearing - Raylib");
    SetTargetFPS(60);

    Point p1, p2, p3;
    int choice;
    float shx = 0, shy = 0;

    printf("Enter triangle vertices (x1 y1 x2 y2 x3 y3): ");
    scanf("%f %f %f %f %f %f", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

    printf("Choose shearing type:\n");
    printf("1. Shear with respect to X-axis\n");
    printf("2. Shear with respect to Y-axis\n");
    printf("3. Shear with respect to both axes\n");
    scanf("%d", &choice);

    char label[100];
    Point sp1 = p1, sp2 = p2, sp3 = p3;

    switch (choice) {
        case 1:
            printf("Enter X-shearing factor (shx): ");
            scanf("%f", &shx);
            shearX(&sp1, shx);
            shearX(&sp2, shx);
            shearX(&sp3, shx);
            sprintf(label, "Shearing with respect to X-axis");
            break;

        case 2:
            printf("Enter Y-shearing factor (shy): ");
            scanf("%f", &shy);
            shearY(&sp1, shy);
            shearY(&sp2, shy);
            shearY(&sp3, shy);
            sprintf(label, "Shearing with respect to Y-axis");
            break;

        case 3:
            printf("Enter X-shearing factor (shx): ");
            scanf("%f", &shx);
            printf("Enter Y-shearing factor (shy): ");
            scanf("%f", &shy);
            shearXY(&sp1, shx, shy);
            shearXY(&sp2, shx, shy);
            shearXY(&sp3, shx, shy);
            sprintf(label, "Shearing with respect to both axes");
            break;

        default:
            printf("Invalid choice!\n");
            CloseWindow();
            return 1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        drawAxes();

        // Original triangle
        drawTriangle(p1, p2, p3, WHITE);

        // Sheared triangle
        Color resultColor = choice == 1 ? CYAN : (choice == 2 ? GREEN : YELLOW);
        drawTriangle(sp1, sp2, sp3, resultColor);

        DrawText(label, 10, 10, 20, WHITE);
        DrawText("Press ESC to exit", 10, 40, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
