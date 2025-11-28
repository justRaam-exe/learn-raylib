#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Learn Make Game using Raylib");
    SetTargetFPS(60); 

    Vector2 playerBall1 = { (float)screenWidth/4, (float)screenHeight/2};
    Vector2 playerBall2 = { (float) screenWidth*3/4, (float)screenHeight/2};


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //playe1 movement
        if (IsKeyDown(KEY_D)) playerBall1.x += 5.0f;
        if (IsKeyDown(KEY_A)) playerBall1.x -= 5.0f;
        if (IsKeyDown(KEY_W)) playerBall1.y -= 5.0f;
        if (IsKeyDown(KEY_S)) playerBall1.y += 5.0f;

        //player2 movement
        if (IsKeyDown(KEY_RIGHT)) playerBall2.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) playerBall2.x -= 5.0f;
        if (IsKeyDown(KEY_UP)) playerBall2.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) playerBall2.y += 5.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(playerBall1, 50, RED);
        DrawCircleV(playerBall2, 50, BLUE);
        DrawText("Player 1: WASD to Move", 10, 10, 20, RED);
        DrawText("Player 2: Arrow Keys to Move", 10, 35, 20, BLUE);
        EndDrawing();
        // Update
        //----------------------------------------------------------------------------------
    }
    CloseWindow();
    return 0;
}