#pragma once
#include"AnimatedTexture.h"
#include"AudioManager.h"

class Ball : public GameEntity
{
private:

	Timer * mTimer;
	Texture * mBallTex;

private:
	
	void HandleMovement();

public:

	Ball();
	~Ball();

	void Update();

	void Render();
};