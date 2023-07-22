#include "ball.hpp"
#include <iostream>


int main()
{
	std::cout << "Starting Game\n";
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth,screenHeight,"PongV2");
	SetTargetFPS(60);


	Ball ball;

	ball.radius = 20;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speedX = 7;
	ball.speedY = 7;

	Paddle player;

	player.width = 25;
	player.height = 120;
	player.x = screenWidth - player.width - 10;
	player.y = screenHeight / 2 - player.height / 2;
	player.speed = 6;

	ComputerPaddle cpu;

	cpu.height = 120;
	cpu.width = 25;
	cpu.x = 10;
	cpu.y = screenHeight / 2 - cpu.height / 2;
	cpu.speed = 6;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ball.Update();
		player.UpdateRect();
		cpu.UpdateComputerRect(ball.y);


		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speedX *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height }))
		{
			ball.speedX *= -1;
		}

		ClearBackground(DarkGreen);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		DrawRectangle(screenWidth / 2,0, screenWidth/2,screenHeight, Green);
		DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen);

		ball.Draw();
		cpu.DrawRect();
		player.DrawRect();

		//Score tracking for both sides
		DrawText(TextFormat("%i",cpuScore), screenWidth/4 -20, 20, 80, WHITE);
		DrawText(TextFormat("%i", playerScore), 3* screenWidth / 4 - 20, 20, 80, WHITE);

		DrawFPS(10, 10); // draws FPS counter

		EndDrawing(); // ends rendering process
	}
	
	CloseWindow();
	return 0;
}