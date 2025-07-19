#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct Point {
    int x;
    int y;
} Point;

int toScreenX(int x) {
    return SCREEN_WIDTH / 2 + x;
}

int toScreenY(int y) {
    return SCREEN_HEIGHT / 2 - y;
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

void translate(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Triangle Translation (Raylib in C)");
    SetTargetFPS(60);

    Point p1, p2, p3;
    int dx, dy;

    printf("Enter triangle vertices (x1 y1 x2 y2 x3 y3): ");
    scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

    printf("Enter translation factors dx and dy: ");
    scanf("%d %d", &dx, &dy);

    Point tp1 = p1;
    Point tp2 = p2;
    Point tp3 = p3;

    translate(&tp1, dx, dy);
    translate(&tp2, dx, dy);
    translate(&tp3, dx, dy);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        drawAxes();
        drawTriangle(p1, p2, p3, WHITE);
        drawTriangle(tp1, tp2, tp3, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
