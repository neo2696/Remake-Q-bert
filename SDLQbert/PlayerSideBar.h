#pragma once

#include "Timer.h"
#include"AudioManager.h"
#include"ScoreBoard.h"
#include"Cube.h"

class PlayerSideBar : public GameEntity
{

private:

	Timer * mTimer;
	AudioManager * mAudio;

	GameEntity * Bar;
	Texture * mPlayer;
	Texture * mPlayerOne;
	Texture * mChangeTo;
	Texture * mMiniCube[4][2];
	Texture * LeftCursor[2];
	Texture * RightCursor[2];
	Texture * CubeColor;
	ScoreBoard * PlayerScore;

	static const int MAX_LIVES = 3;
	GameEntity * mQbert;
	Texture * mQbertTexture[MAX_LIVES];
	int	 TotalLives;
	int mRound;
	int mLevel;


public:

	PlayerSideBar();
	~PlayerSideBar();

	void SetPlayerScore(int score);

	void SetPlayerLives(int lives);

	void SetMiniCube(int round,int level);

	void Update();

	void Render();
};
