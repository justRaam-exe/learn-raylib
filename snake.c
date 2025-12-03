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

    while (!WindowShouldCLose()) {
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


}