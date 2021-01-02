#pragma once
#include"InputManager.h"
#include "AnimatedTexture.h"
#include "PlaySideBar.h"
#include"Player.h"
#include"PlayerSideBar.h"
#include"Cube.h"
#include"Coily.h"
#include"Ball.h"
#include"GreenBall.h"
#include"Disk.h"
class Level : public GameEntity
{
private:

	Timer * mTimer;
	AudioManager * mAudio;
	PlaySideBar *Right;

	int mRound;
	int mLevel;
	bool mLevelStarted;

	float mLabelTimer;

	Texture *mLevelLabel;
	ScoreBoard *mLevelNumber;

	float mLevelOnScreen;
	float mLevelOffScreen;

	Texture *mRoundLabel;
	ScoreBoard *mRoundNumber;

	bool mLevelOver;

	//Player

	Player * mPlayer;
	//Level Entities
	Cube * mCube[7][7];

	Coily * mEnemySnake;

	Ball * mBall[10];
	GreenBall * mPowerUP;
	bool mflag1;

	Disk * mdisk1;
	Disk * mdisk2;

	PlayerSideBar * mBAR;
	static const int MAX_BOUNCES = 28;
	bool  mFlagCube;
	bool flag[10];

private:

	void StartRound();

	void Collision(Player * player , Cube * box);

	

public:

	Level(int level, int round,PlaySideBar * sidebar, Player* player,PlayerSideBar * BAR,Coily * enemy,Ball * balls[10],GreenBall * power,Disk * disk1,Disk * disk2);
	~Level();

	void Reset(int level,int round);

	void EnemiesReset();

	bool GameStop();

	bool LevelOver();

	void Update();

	void Render();
	 
};