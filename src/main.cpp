#include "raylib.h"
#include "raymath.h"
#include "camera.h"
#include "player.h"
#include <format>
#include <string>
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point - FPS Camera Test
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "FPS Camera Test");

    // Create FPS camera - position, front direction, up normal, sensitivity, yaw, pitch, fovy
    Player player(Vector3{ 0.0f, 2.0f, 5.0f });
    // Hide cursor and enable raw mouse input for FPS controls
    DisableCursor();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // Get mouse delta for camera rotation
        // Vector2 mouseDelta = GetMouseDelta();
        // std::cout << "mouseDelta.x " << mouseDelta.x << " mouseDelta.y " << mouseDelta.y << std::endl;
        // std::cout << "fpsCamera.getDirection().x " << fpsCamera.getDirection().x << " fpsCamera.getDirection().y " << fpsCamera.getDirection().y << " fpsCamera.getDirection().z " << fpsCamera.getDirection().z << std::endl;
        
        player.update();
        // Toggle cursor with H key
        if (IsKeyPressed(KEY_H))
        {
            if (IsCursorHidden()) ShowCursor();
            else DisableCursor();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            Camera3D camera = player.getCamera();
            BeginMode3D(camera);

                // Draw grid
                DrawGrid(20, 1.0f);

                // Draw some cubes for reference
                DrawCube(Vector3{ -5.0f, 1.0f, -5.0f }, 2.0f, 2.0f, 2.0f, RED);
                DrawCube(Vector3{ 5.0f, 1.0f, -5.0f }, 2.0f, 2.0f, 2.0f, GREEN);
                DrawCube(Vector3{ -5.0f, 1.0f, 5.0f }, 2.0f, 2.0f, 2.0f, BLUE);
                DrawCube(Vector3{ 5.0f, 1.0f, 5.0f }, 2.0f, 2.0f, 2.0f, YELLOW);
                
                // Draw a central sphere
                DrawSphere(Vector3{ 0.0f, 1.0f, 0.0f }, 1.0f, ORANGE);

                // Draw some pillars
                for (int i = -10; i <= 10; i += 5)
                {
                    for (int j = -10; j <= 10; j += 5)
                    {
                        if (i == 0 && j == 0) continue;
                        DrawCylinder(Vector3{ (float)i, 0.0f, (float)j }, 0.3f, 0.3f, 3.0f, 8, GRAY);
                    }
                }

            EndMode3D();

            // Draw UI overlay
            DrawText("FPS CAMERA TEST", 10, 10, 20, DARKBLUE);
            DrawText("----------------", 10, 30, 20, DARKBLUE);
            DrawText("WASD - Move forward/backward/strafe", 10, 60, 16, DARKGRAY);
            DrawText("SPACE - Move up", 10, 80, 16, DARKGRAY);
            DrawText("LEFT_CTRL - Move down", 10, 100, 16, DARKGRAY);
            DrawText("MOUSE - Look around", 10, 120, 16, DARKGRAY);
            DrawText("H - Toggle cursor", 10, 140, 16, DARKGRAY);
            DrawText("----------------", 10, 160, 20, DARKBLUE);

            // Display current camera position
            Vector3 position = player.getPosition();
            std::string posText = std::format("Position: [{:.2f}, {:.2f}, {:.2f}]", 
                position.x, position.y, position.z);
            DrawText(posText.c_str(), 10, 200, 18, DARKGREEN);

            // Display FPS
            int fps = GetFPS();
            std::string fpsText = std::format("FPS: {}", fps);
            DrawText(fpsText.c_str(), screenWidth - 100, 20, 24, 
                fps >= 55 ? GREEN : (fps >= 30 ? YELLOW : RED));

            if (IsCursorHidden())
            {
                DrawText("CURSOR HIDDEN (FPS Mode)", screenWidth - 250, 50, 16, RED);
            }
            else
            {
                DrawText("CURSOR VISIBLE", screenWidth - 200, 50, 16, LIME);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    EnableCursor();
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}
