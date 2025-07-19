#include <raylib.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib - House Drawing");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Ground
        DrawRectangle(0, 500, 800, 100, GREEN);

        // House base
        DrawRectangle(300, 300, 200, 200, BROWN);

        // Roof (triangle)
        DrawTriangle(
            (Vector2){290, 300},
            (Vector2){510, 300},
            (Vector2){400, 200},
            MAROON
        );

        // Door
        DrawRectangle(375, 400, 50, 100, DARKGRAY);

        // Door knob
        DrawCircle(420, 450, 5, GOLD);

        // Windows
        DrawRectangle(320, 330, 40, 40, SKYBLUE);
        DrawRectangle(440, 330, 40, 40, SKYBLUE);

        // Window panes
        DrawLine(340, 330, 340, 370, DARKBLUE); // vertical pane left
        DrawLine(320, 350, 360, 350, DARKBLUE); // horizontal pane left
        DrawLine(460, 330, 460, 370, DARKBLUE); // vertical pane right
        DrawLine(440, 350, 480, 350, DARKBLUE); // horizontal pane right

        // Title
        DrawText("A Simple House - Raylib (C)", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
