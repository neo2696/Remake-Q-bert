#include"GreenBall.h"
int K = 1;

GreenBall::GreenBall()
{
	mTimer = Timer::Instance();

	mBallTex = new Texture("GreenBall.png");

	mBallTex->Parent(this);
	mBallTex->Pos(VEC2_ZERO);
}

GreenBall::~GreenBall()
{
	mTimer = NULL;
	delete mBallTex;
	mBallTex = NULL;
}

void GreenBall::HandleMovement()
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

void GreenBall::Update()
{
	if (Active())
	{
		K++;
		if (K % 50 == 0)
		{
			HandleMovement();
		}
	}
}

void GreenBall::Render()
{
	if (Active())
	{
		mBallTex->Render();
	}
}