#include "raylib.h"
#include "raylibtest.h"


void BallDraw(Ball *ball)
{
    DrawCircle(ball->x, ball->y, ball->radius, GREEN);
}


void BoardDraw(Board *board)
{
    DrawRectangle(board->x - (board->width / 2), board->y - (board->height/ 2), 10, 100, WHITE);
}

void GetRect(Board* board,Rectangle* rect)
{
    rect->x = board->x - (board->width / 2);
    rect->y = board->y - (board->height / 2);
    rect->width = 10;
    rect->height = 100;
}

//void Draw(Board *board)
//{
//	DrawRectangleRec(GetRect(&leftPaddle), WHITE));
//}

int main(void)
{
    InitWindow(800,600,"Pong");
    
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    
    ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
    ball.ballSpeedX;
   
    ball.radius = 5.0;
    ball.ballSpeedX = 300.0;
	ball.ballSpeedY = 300.0;

    Board leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2.0f;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.boardSpeed = 500.0;

    Board rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight() / 2.0f;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.boardSpeed = 500.0;

    while (!WindowShouldClose())
    {

        // ball movement
        ball.x+= ball.ballSpeedX * GetFrameTime(); // moves the ball across
        ball.y+= ball.ballSpeedY * GetFrameTime(); // moves the ball up down


        // ball collision
        if (ball.y < 0) 
        {
            ball.y = 0;
            ball.ballSpeedY *= -1;
        }

        if (ball.y > GetScreenHeight())

        {
                ball.y= GetScreenHeight(); // keeps the ball on screen
                ball.ballSpeedY *= -1; // reverses the ball direction if it goes off screen
        }

        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= leftPaddle.boardSpeed * GetFrameTime();
        }

        if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += leftPaddle.boardSpeed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.y -= rightPaddle.boardSpeed * GetFrameTime();
        }

        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.y += rightPaddle.boardSpeed * GetFrameTime();
        }

       Vector2 ballPosition = { ball.x,ball.y };
       Rectangle rightPaddleRect;
       Rectangle leftPaddleRect;
       GetRect(&rightPaddle, &rightPaddleRect);
       GetRect(&leftPaddle, &leftPaddleRect);


        if (CheckCollisionCircleRec(ballPosition,ball.radius, rightPaddleRect))
        {
            ball.ballSpeedX *= -1;
        }
        if (CheckCollisionCircleRec(ballPosition, ball.radius, leftPaddleRect))
        {
            ball.ballSpeedX *= -1;
        }
        //Action
        BeginDrawing(); // starts rendering process
            ClearBackground(BLACK); // sets background color

            BallDraw(&ball); // draws ball
            BoardDraw(&leftPaddle); // draws board
            BoardDraw(&rightPaddle);

            DrawFPS(10,10); // draws FPS counter

        EndDrawing(); // ends rendering process
    }

    CloseWindow();
    
    return 0;
}