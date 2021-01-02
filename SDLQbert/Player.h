#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include"AudioManager.h"


class Player : public GameEntity
{

private:

	Timer * mTimer;
	InputManager * mInput;
	AudioManager *mAudio;

	bool mVisible;
	bool mAnimating;

	int mbounce;
	int mScore;
	int mLives;

	bool flags[4];
	int lastkey;

	float MoveSpeed;
	Vector2 MinMoveBounds;
	Vector2 MaxMoveBounds;

	Texture * mDeath;
	AnimatedTexture * mJumpAnimationA;
	AnimatedTexture * mJumpAnimationD;
	AnimatedTexture * mJumpAnimationQ;
	AnimatedTexture * mJumpAnimationE;
	AnimatedTexture* mJumpAnimation[4];
	Texture * mQbert[4];
	bool mdeathflag;

private:

	void HandleMovement();

public:

	Player();
	~Player();

	void Visible(bool visible);

	bool IsAnimating();

	bool  GetFlagsStatus(char ch);

	int Score();
	int Lives();

	void AddScore(int change);


	void WasHit();

	void WentOutofBounds();

	int Bounce();
	
	void CubeLanded();

	void SetDeathFlag(bool val);

	void Update();

	void Render();

};