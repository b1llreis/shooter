#include "raylib.h"
#include <math.h>

int main() {
    InitWindow(800, 600, "My Shooter");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = { 5.0f, 5.0f, 5.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float rotation = 0.0f;

    while (!WindowShouldClose()) {
        rotation += 3.0f;

        BeginDrawing();
            float angle = rotation * DEG2RAD;
            camera.position.x = 5.0f * cosf(rotation * DEG2RAD);
            camera.position.z = 5.0f * sinf(rotation * DEG2RAD);
            ClearBackground(SKYBLUE);

            BeginMode3D(camera);
                DrawGrid(20, 1.0f);
                
                Vector3 cubePos = { 0.0f, 1.0f, 0.0f };
                DrawCube(cubePos, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, DARKGRAY);
            EndMode3D();

            DrawText("3D works!", 10, 10, 20, WHITE);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}