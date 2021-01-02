#pragma once
#include"InputManager.h"
#include"Timer.h"
#include"PlayerSideBar.h"
#include"Level.h"
class PlayScreen : public GameEntity
{

private:

	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;

	Texture * mStartLabel;
	Texture *mEndLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentLevel;
	int mCurrentRound;

	Level * mLevel;

	PlaySideBar * mRight;
	PlayerSideBar * mLeftSidebar;
	
	AnimatedTexture * mAnimateDisk;

	Player * mPlayer;
	Coily * mEnemy;
	Ball * balls[10];
	GreenBall * power;

	Disk * disk1;
	Disk * disk2;
	bool mGameOver;


public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	
	void Update();

	void Render();




private:

	void StartNextLevel();
	void StartFirstLevel();
};