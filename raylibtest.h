

typedef struct Ball_
{

    float x, y;
    float ballSpeedX, ballSpeedY;
    float radius;


} Ball;

void BallDraw(Ball *ball);



typedef struct Board_
{
	float x, y;
	float boardSpeed;
	float width, height;

} Board;

void BoardDraw(Board *board);