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
    
   // Sets ball in middle of screen
    ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
    ball.ballSpeedX; // ball speed in x direction
   
    //Radius of ball
    ball.radius = 5.0;
    ball.ballSpeedX = 300.0;
	ball.ballSpeedY = 300.0;

    //Setting paddle size/speed
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

    // Main game loop
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

        // Paddle Movement
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

      
       Vector2 ballPosition = { ball.x,ball.y }; // vector2 for the ball position
       Rectangle rightPaddleRect; // rectangle for the right paddle
       Rectangle leftPaddleRect; // rectangle for the left paddle
       GetRect(&rightPaddle, &rightPaddleRect); // gets the rectangle for the right paddle
       GetRect(&leftPaddle, &leftPaddleRect); // gets the rectangle for the left paddle

       const char* winner = NULL; // sets the winner to null


       //Collison check between ball and paddles

       //Left paddle
        if (CheckCollisionCircleRec(ballPosition, ball.radius, leftPaddleRect)) //
        {
            if (ball.ballSpeedX < 0)
            {
                ball.ballSpeedX *= -1.1f;
                ball.ballSpeedY = (ball.y - leftPaddle.y)/(leftPaddle.height/2) * ball.ballSpeedX;
            }
        }
        //Right paddle
        if (CheckCollisionCircleRec(ballPosition, ball.radius, rightPaddleRect))
        {
            if (ball.ballSpeedX > 0)
            {
				ball.ballSpeedX *= -1.1f;
                ball.ballSpeedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.ballSpeedX;
			}
        }
        
        //Win condition
        if (ball.x < 0) // if the ball goes off the left side of the screen
        {
            winner = "Right Paddle Wins!";
        }

        if (ball.x > GetScreenWidth()) // if the ball goes off the right side of the screen
        {
			winner = "Left Paddle Wins!";
            
		}

        //Reset conditions after winning
        if (winner && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2.0f;
            ball.y = GetScreenHeight() / 2.0f;
            ball.ballSpeedX = 300.0;
            ball.ballSpeedY = 300.0;
            winner = NULL;
        }

        //Action
        BeginDrawing(); // starts rendering process
            ClearBackground(BLACK); // sets background color

            BallDraw(&ball); // draws ball
            BoardDraw(&leftPaddle); // draws board
            BoardDraw(&rightPaddle); // draws board


            // if there is a winner, draw the text
            if (winner) 
            {
                int width = MeasureText(winner, 60);
                DrawText(winner, (GetScreenWidth() / 2) - (width/2), (GetScreenHeight() / 2), 60, YELLOW); // centers the text
            }

            DrawFPS(10,10); // draws FPS counter

        EndDrawing(); // ends rendering process
    }

    CloseWindow();
    
    return 0;
}