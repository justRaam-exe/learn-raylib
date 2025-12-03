#include "raylib.h"

#define snake_length 256
#define square_size 20

typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food {
    Vector2 position;
    Vector2 size;
    Color color;
    bool active;
} Food;

// Declare a Variables Section

// screen variables
static const int screenWidth = 1280;
static const int screenHeight = 720;

// game variables
static int framesCounter = 0;
static bool gameOver = false;
static bool pause = false;

// character variables
static Food fruit = { 0 };
static Snake snake[snake_length] = { 0 };
static Vector2 snakePositions[snake_length] = { 0 };
static bool allowMove = false;
static Vector2 offset = { 0 };
static int counterTail = 0;

// Declare a Module
static void InitGame(void);        // Initialize game variables
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(void);        // Draw game (one frame)
static void UnloadGame(void);      // Unload game variables
static void UpdateDrawFrame(void); // Update and Draw (one frame)

// Main Program Entry Point
int main(void) {
    InitWindow(screenWidth, screenHeight, "Snake Game - Raam");

    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
    UnloadGame();
    CloseWindow();
    return 0;
}

void InitGame(void) {
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;
    allowMove = false;

    offset.x = screenWidth%square_size;
    offset.y = screenHeight%square_size;

    for (int i = 0; i < snake_length; i++) {
        snake[i].position = (Vector2){ offset.x/2, offset.y/2 };
        snake[i].size = (Vector2){ square_size, square_size };
        snake[i].speed = (Vector2){square_size, 0};

        if (i == 0) snake[i].color = DARKBROWN;
        else snake[i].color = BROWN;
    }

    for (int i = 0; i < snake_length; i++) {
        snakePositions[i] = (Vector2){0.0f, 0.0f};
    }

    fruit.size = (Vector2){square_size, square_size};
    fruit.color = DARKBLUE;
    fruit.active = false;
}

void UpdateGame(void) {
    if (!gameOver) {
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if(!pause) {
            // Handle Player Movement

            // Move Right
            if (IsKeyPressed(KEY_D) && (snake[0].speed.x == 0)) {
                snake[0].speed = (Vector2){square_size, 0};
                allowMove = false;
            }

            // Move Left
            if (IsKeyPressed(KEY_A) && (snake[0].speed.x == 0)) {
                snake[0].speed = (Vector2){-square_size, 0};
                allowMove = false;
            }

            // Move Up
            if (IsKeyPressed(KEY_W) && (snake[0].speed.y == 0)) {
                snake[0].speed = (Vector2){0, -square_size};
                allowMove = false;
            } 

            // Move Down
            if (IsKeyPressed(KEY_S) && (snake[0].speed.y == 0)) {
                snake[0].speed = (Vector2){0, square_size};
                allowMove = false;
            }

            // Snake Movement
            for (int i = 0; i < counterTail; i++) {
                snakePositions[i] = snake[i].position;
            }

            if((framesCounter%4) == 0) {
                for (int i = 0; i < counterTail; i++) {
                    if (i == 0) {
                        snake[0].position.x += snake[0].speed.x;
                        snake[0].position.y += snake[0].speed.y;
                        allowMove = true;
                    } else {
                        snake[i].position = snakePositions[i-1];
                    }
                }
            }

            // Check Wall Collision
            if (((snake[0].position.x) > (screenWidth - offset.x)) ||
                ((snake[0].position.y) > (screenHeight - offset.y))||
                (snake[0].position.x < 0) ||
                (snake[0].position.y < 0)) {
                    gameOver = true;
            }
          
            // Check Self Collision
            for (int i = 1; i < counterTail; i++) {
                if ((snake[0].position.x == snake[i].position.x) &&
                    (snake[0].position.y == snake[i].position.y)) {
                    gameOver = true;
                }
            }

            // Handle Fruit Position
            if (!fruit.active) {
                fruit.active = true;
                fruit.position = (Vector2){GetRandomValue(0, (screenWidth/square_size) - 1)*square_size + offset.x/2,
                                           GetRandomValue(0, (screenHeight/square_size) - 1)*square_size + offset.y/2};
                
                for (int i = 0; i < counterTail; i++) {
                    while((fruit.position.x == snake[i].position.x) && (fruit.position.y == snake[i].position.y)) {
                        fruit.position = (Vector2){GetRandomValue(0, (screenWidth/square_size) - 1)*square_size + offset.x/2,
                                                GetRandomValue(0, (screenHeight/square_size) - 1)*square_size + offset.y/2};
                        i = 0;
                    }
                }
            }

            // Check Fruit Collision
            if ((snake[0].position.x < (fruit.position.x + fruit.size.x) && (snake[0].position.x + snake[0].size.x) > fruit.position.x) &&
                (snake[0].position.y < (fruit.position.y + fruit.size.y) && (snake[0].position.y + snake[0].size.y) > fruit.position.y)) {
                snake[counterTail].position = snakePositions[counterTail - 1];
                counterTail += 1;
                fruit.active = false;
            }

            framesCounter++;
        }
    }
    else {
        if (IsKeyPressed(KEY_ENTER)) {
            InitGame();
            gameOver = false;
        }
    }
}

void DrawGame(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    if(!gameOver) {
        for (int i = 0; i < counterTail; i++) {
            DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
        }

        DrawRectangleV(fruit.position, fruit.size, fruit.color);

        if (pause) {
            DrawText("PAUSED", screenWidth/2 - MeasureText("PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
    } else {
        DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 40)/2, screenHeight/2 - 40, 40, RED);
        DrawText("Press ENTER to Restart", screenWidth/2 - MeasureText("Press ENTER to Restart", 20)/2, screenHeight/2 + 20, 20, DARKGRAY);
    }
    EndDrawing();
}

void UnloadGame(void) {

}

void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}