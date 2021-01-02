#pragma once
#include"Timer.h"
#include"Texture.h"

class AnimatedTexture : public Texture
{
public:

	enum WRAP_MODE { once=0,loop=1};
	enum ANIM_DIR {horizontal =0 , vertical=1};

private:
	Timer * mTimer;

	int mStartx;
	int mStarty;

	float mAnimationTimer;
	float mAnimationSpeed;
	float mTimerPerFrame;

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimationDirection;

	bool mAnimationDone;

public:

	AnimatedTexture(string filename, int x, int y, int w, int h, int frameCount, float AnimationSpeed, ANIM_DIR animationDir);
	~AnimatedTexture();
	
	
	void WrapMode(WRAP_MODE mode);

	void ResetAnimation();

	bool IsAnimating();

	void Update();
};