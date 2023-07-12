#include "raylib.h"
#include "raymath.h"

typedef struct Ball_
{
    float x, y;
    float ballSpeedX, ballSpeedY;
    float radius;


} Ball;



int main(void)
{
    InitWindow(800,600,"Pong");
    
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    
    ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
    ball.ballSpeedX;
   
    ball.radius = 5.0;
    ball.ballSpeedX = 100.0;
	ball.ballSpeedY = 300.0;

    while (!WindowShouldClose())
    {
        ball.x+= ball.ballSpeedX * GetFrameTime(); // moves the ball across
        ball.y+= ball.ballSpeedY * GetFrameTime(); // moves the ball up down

        if (ball.y < 0) {
            ball.y = 0;
            ball.ballSpeedY *= -1;
        }

        if (ball.y > GetScreenHeight())

        {
                ball.y= GetScreenHeight(); // keeps the ball on screen
                ball.ballSpeedY *= -1; // reverses the ball direction if it goes off screen
        }
        BeginDrawing(); // starts rendering process
            ClearBackground(BLACK); // sets background color

            DrawCircle((int) ball.x,(int)ball.x, ball.radius, GREEN); // draws a circle in the center
            DrawRectangle(50, ball.y -50, 10, 100, WHITE); // left rectangle
            DrawRectangle(GetScreenWidth() - 50 -10, ball.y - 50, 10, 100, WHITE); // right rectangle

            DrawFPS(10,10); // draws FPS counter

        EndDrawing(); // ends rendering process
    }

    CloseWindow();
    
    return 0;
}