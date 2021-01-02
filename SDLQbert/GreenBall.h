#pragma once

#include"AnimatedTexture.h"
#include"AudioManager.h"

class GreenBall : public GameEntity
{
private:

	Timer * mTimer;
	Texture * mBallTex;

private:

	void HandleMovement();

public:

	GreenBall();
	~GreenBall();

	void SetBallType(int t);

	void Update();

	void Render();
};