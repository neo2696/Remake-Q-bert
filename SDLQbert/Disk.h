#pragma once
#include"AnimatedTexture.h"
#include"AudioManager.h"

class Disk :public GameEntity
{

private:

	AnimatedTexture * mDiskTex[4];
	Timer * mTimer;
	AudioManager * mAudio;
	bool mAnimating;
	int roundnum;

private:


public:

	Disk();
	~Disk();

	bool IsAnimating();

	void SetAnimating(bool val);

	void GetRound(int r);

	void Update();

	void Render();
};