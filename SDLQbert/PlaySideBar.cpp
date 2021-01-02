#include "PlaySideBar.h"

PlaySideBar::PlaySideBar()
{

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mLevel = new Texture("LEVEL ", "Q-bert Original.ttf", 22, { 0,250,0 });
	mRound = new Texture("ROUND ", "Q-bert Original.ttf", 22, { 255,192,203});
	mHighscore = new Texture("HIGH SCORE ", "Q-bert Original.ttf", 22, { 255,192,203 });

	
	HighScore = new ScoreBoard();

	mLevelNumber = new ScoreBoard();
	mRoundNumber = new ScoreBoard();

	
	mHighscore->Pos(Vector2(600, 50));
	HighScore->Pos(Vector2(650, 80));
	mLevel->Pos(Vector2(600, 120));
	mRound->Pos(Vector2(600, 160));
	mLevelNumber->Pos(Vector2(670, 120));
	mRoundNumber->Pos(Vector2(670, 160));
	HighScore->Parent(this);

}

PlaySideBar ::~PlaySideBar()
{
	delete mLevel;
	mLevel = NULL;

	delete mRound;
	mRound = NULL;

	mTimer = NULL;
	mAudio = NULL;

	delete mHighscore;
	mHighscore = NULL;

	delete HighScore;
	HighScore = NULL;

	delete mLevelNumber;
	mLevelNumber = NULL;

	delete mRoundNumber;
	mRoundNumber = NULL;
}

void PlaySideBar::SetLevel(int level,int round)
{
	mLevelNumber->SetScore(level);
	mRoundNumber->SetScore(round);
}

void PlaySideBar::SetHighScore(int score)
{
	HighScore->SetScore(score);
}

int  PlaySideBar::GetHighScore()
{
	int t = (int)HighScore;
	return t;
}

void PlaySideBar::Update()
{



}

void PlaySideBar::Render()
{
	mLevel->Render();
	mRound->Render();
	mHighscore->Render();
	HighScore->Render();
	mLevelNumber->Render();
	mRoundNumber->Render();

}