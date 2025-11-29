#include "raylib.h"
#include <math.h>

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen; 

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Basic Game Raylib Example");
    
    SetExitKey(KEY_NULL);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    GameScreen currentScreen = LOGO;
    int framesCounter = 0;

    SetTargetFPS(60); 

    Vector2 playerBall1 = { (float)screenWidth/4, (float)screenHeight/2};
    Vector2 playerBall2 = { (float) screenWidth*3/4, (float)screenHeight/2};
    float ballRadius = 50.0f;


    while (!exitWindow) 
    {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

        if (exitWindowRequested)
        {
            if(IsKeyPressed(KEY_Y)) exitWindow = true;
            else if(IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        else
        {
            switch (currentScreen)
            {
                case LOGO:
                {
                    framesCounter++;
                    if (framesCounter > 180)
                    {
                        currentScreen = TITLE;
                    }
                } break;
                case TITLE:
                {
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        currentScreen = GAMEPLAY;
                    }
                } break;
                case GAMEPLAY:
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

                    if (IsKeyPressed(KEY_ENTER))
                    {
                        currentScreen = ENDING;
                    }
                } break;
                case ENDING:
                {
                    if (IsKeyPressed(KEY_ENTER)) 
                    {
                        currentScreen = TITLE;
                    }
                } break;
                default: break;
            }
        }
        
        

        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    DrawText("LOGO SCREEN", 20, 20, 40, BLACK);
                    DrawText("WAIT for 3 SECONDS...", 290, 220, 20, BLACK);
                } break;
                case TITLE:
                {
                    DrawText("TITLE SCREEN", 120, 220, 20, BLACK);
                    DrawText("Press ENTER to START THE GAME", 120, 250, 20, BLACK);
                } break;
                case GAMEPLAY:
                {
                    DrawText("Player 1: WASD to Move", 10, 10, 20, RED);
                    DrawText("Player 2: Arrow Keys to Move", 10, 35, 20, BLUE);
                    DrawText("Press ENTER to END THE GAME", 10, 60, 20, BLACK);
                    DrawCircleV(playerBall1, ballRadius, RED);
                    DrawCircleV(playerBall2, ballRadius, BLUE);
                } break;
                case ENDING:
                {
                    DrawText("Press ENTER to RETURN to TITLE SCREEN", 120, 220, 20, BLACK);
                    DrawText("Press ESC to EXIT", 120, 250, 20, BLACK);
                    if (exitWindowRequested)
                    {
                        DrawRectangle(0, 100, screenWidth, 200, BLACK);
                        DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
                    }
                }
            }
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}