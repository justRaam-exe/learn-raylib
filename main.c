#include "raylib.h"
#include <math.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Basic Game Raylib Example");
    SetTargetFPS(60); 

    Vector2 playerBall1 = { (float)screenWidth/4, (float)screenHeight/2};
    Vector2 playerBall2 = { (float) screenWidth*3/4, (float)screenHeight/2};
    float ballRadius = 50.0f;


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

        //boundary check for player 1
        if (playerBall1.x < ballRadius) playerBall1.x = ballRadius;
        if (playerBall1.x > screenWidth - ballRadius) playerBall1.x = screenWidth - ballRadius;
        if (playerBall1.y < ballRadius) playerBall1.y = ballRadius;
        if (playerBall1.y > screenHeight - ballRadius) playerBall1.y = screenHeight - ballRadius;

        //boundary check for player 2
        if (playerBall2.x < ballRadius) playerBall2.x = ballRadius;
        if (playerBall2.x > screenWidth - ballRadius) playerBall2.x = screenWidth - ballRadius;
        if (playerBall2.y < ballRadius) playerBall2.y = ballRadius;
        if (playerBall2.y > screenHeight - ballRadius) playerBall2.y = screenHeight - ballRadius;

        if (CheckCollisionCircles(playerBall1, ballRadius, playerBall2, ballRadius))
        {
            // Hitung jarak antara 2 bola
            float dx = playerBall2.x - playerBall1.x;
            float dy = playerBall2.y - playerBall1. y;
            float distance = sqrtf(dx * dx + dy * dy);
            
            // Hitung overlap (seberapa dalam bola saling menembus)
            float overlap = (ballRadius * 2) - distance;
            
            // Pisahkan kedua bola
            if (distance > 0)
            {
                // Normalisasi vektor arah
                dx /= distance;
                dy /= distance;
                
                // Dorong masing-masing bola setengah dari overlap
                playerBall1.x -= dx * overlap / 2;
                playerBall1.y -= dy * overlap / 2;
                playerBall2.x += dx * overlap / 2;
                playerBall2.y += dy * overlap / 2;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(playerBall1, 50, RED);
        DrawCircleV(playerBall2, 50, BLUE);
        DrawText("Player 1: WASD to Move", 10, 10, 20, RED);
        DrawText("Player 2: Arrow Keys to Move", 10, 35, 20, BLUE);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}