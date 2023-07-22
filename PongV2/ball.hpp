#pragma once

#include "raylib.h"

Color Green = Color{ 38,185,154,255 };
Color DarkGreen = Color{ 20, 160, 133, 255 };
Color LightGreen = Color{ 46, 204, 113, 255 };
Color Orange = Color{ 243, 156, 18, 255 };

int playerScore = 0;
int cpuScore = 0;

class Ball
{
public:
	float x, y;
	int speedX, speedY;
	int radius;

	void Draw()
	{
		DrawCircle(x,y,radius, Orange);
	}
	
	void Update()
	{
		x += speedX;
		y += speedY;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speedY *= -1;
		}
		if (x + radius >= GetScreenWidth())
		{
			cpuScore++;
			ResetBall();
		}
		
		if (x - radius <= 0)
		{
			playerScore++;
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		int speedOptions[2] = { -1,1 };
		speedX *= speedOptions[GetRandomValue(0,1)];
		speedY *= speedOptions[GetRandomValue(0, 1)];
	}

};

class Paddle
{
protected:

	void MovementLimit() 
	{
		if (y <= 0)
		{
			y = 0;
		}
		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}
	}

public:

float x, y;
float width, height;
int speed;

void DrawRect()
{
	DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.8, 0, WHITE);
}

void UpdateRect()
{
	if (IsKeyDown(KEY_UP))
	{
		y -= speed;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		y += speed;
	}

	MovementLimit();
}

};

// computer paddle for the left side
class ComputerPaddle: public Paddle
{
public:
	void UpdateComputerRect(int ball_y)
	{
		if (y + height/2> ball_y)
		{
			y -= speed; 

		}

		if (y + height / 2 <= ball_y)
		{
			y += speed;

		}

		MovementLimit();
	}

};