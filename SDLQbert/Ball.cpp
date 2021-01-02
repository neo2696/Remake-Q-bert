#include"Ball.h"
int J = 1;
Ball::Ball()
{
	mTimer = Timer::Instance();

	mBallTex = new Texture("RedBall.png");

		mBallTex->Parent(this);
		mBallTex->Pos(VEC2_ZERO);
}

Ball::~Ball()
{
	mTimer = NULL;

		delete mBallTex;
		mBallTex = NULL;
}

void Ball::HandleMovement()
{
	if (rand() % 2 == 0)
	{
		Translate(Vector2(-30, 52));

	}
	else
	{
		Translate(Vector2(30, 52));
	}
}



void Ball::Update()
{
	if (Active())
	{
		J++;
		if (J % 40 == 0)
		{
			HandleMovement();
		}
	}
}

void Ball::Render()
{
	if (Active())
	{
		mBallTex->Render();
	}
}