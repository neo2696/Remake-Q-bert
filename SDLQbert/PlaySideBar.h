#pragma once
#include "Timer.h"
#include"AudioManager.h"
#include"ScoreBoard.h"
class PlaySideBar : public GameEntity
{

private:

	Timer * mTimer;
	AudioManager * mAudio;

	Texture * mLevel;
	ScoreBoard * mLevelNumber;
	ScoreBoard *mRoundNumber;
	Texture * mRound;
	Texture * mHighscore;
	ScoreBoard * HighScore;

public:

	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);

	void SetLevel(int level,int round);

	int GetHighScore();

	void Update();

	void Render();
};