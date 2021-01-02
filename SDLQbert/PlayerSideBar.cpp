#include"PlayerSideBar.h"

PlayerSideBar::PlayerSideBar()
{

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	
	PlayerScore = new ScoreBoard();

	RightCursor[0] = new Texture("Cursor.png");
	RightCursor[1] = new Texture("Cursor.png");
	LeftCursor[0] = new Texture("LeftCursor.png");
	LeftCursor[1] = new Texture("LeftCursor.png");
	mPlayer = new Texture("Player.png");
	mPlayerOne = new Texture("Number 1.png");
	mChangeTo = new Texture("CHANGE TO ", "Q-bert Original.ttf", 20, { 255,0,0 });

	mMiniCube[0][0] = new Texture("Mini Cube12.png");
	mMiniCube[0][1] = new Texture("Mini Cube13.png");
	mMiniCube[1][0] = new Texture("Mini Cube21.png");
	mMiniCube[1][1] = new Texture("Mini Cube22.png");
	mMiniCube[2][0] = new Texture("Mini Cube31.png");
	mMiniCube[2][1] = new Texture("Mini Cube32.png");
	mMiniCube[3][0] = new Texture("Mini Cube41.png");
	mMiniCube[3][1] = new Texture("Mini Cube42.png");


	mPlayer->Pos(Vector2(100, 50));
	mPlayerOne->Pos(Vector2(180, 50));
	PlayerScore->Pos(Vector2(120, 80));
	
	
	mChangeTo->Pos(Vector2(120, 160));
	
	RightCursor[0]->Pos(Vector2(60, 180));
	RightCursor[1]->Pos(Vector2(85, 180));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mMiniCube[i][j]->Pos(Vector2(115, 180));
		}
	}
	LeftCursor[0]->Pos(Vector2(145, 180));
	LeftCursor[1]->Pos(Vector2(170, 180));


	mQbert = new GameEntity();
	mQbert->Parent(this);
	mQbert->Pos(Vector2(50 ,270 ));


	for (int i = 0; i < MAX_LIVES; i++)
	{
		mQbertTexture[i] = new Texture("QBert Lives.png");
		mQbertTexture[i]->Parent(mQbert);
		mQbertTexture[i]->Pos(Vector2(32 * (i / 3), 32 * (i % 3)));
	}
}

PlayerSideBar ::~PlayerSideBar()
{
	delete PlayerScore;
	PlayerScore = NULL;

	delete RightCursor[0];
	RightCursor[0] = NULL;

	delete RightCursor[1];
	RightCursor[1] = NULL;

	delete LeftCursor[0];
	LeftCursor[0] = NULL;

	delete LeftCursor[1];
	LeftCursor[1] = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mPlayerOne;
	mPlayerOne = NULL;

	delete mChangeTo;
	mChangeTo = NULL;

	delete Bar;
	Bar = NULL;
	
	mTimer = NULL;
	mAudio = NULL;


	delete mQbert;
	mQbert = NULL;

	for (int i = 0; i < MAX_LIVES; i++)
	{
		delete mQbertTexture[i];
		mQbertTexture[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			delete mMiniCube[i][j];
			mMiniCube[i][j] = NULL;
		}
	}
}

void PlayerSideBar::SetPlayerLives(int lives)
{
	TotalLives = lives;
}

void PlayerSideBar::SetPlayerScore(int score)
{
	PlayerScore->SetScore(score);
}

void PlayerSideBar::Update()
{

}

void PlayerSideBar::SetMiniCube(int round,int level)
{
	mRound = round;
	mLevel = level;
}

void PlayerSideBar::Render()
{
	mPlayer->Render();
	mPlayerOne->Render();
	PlayerScore->Render();
	mChangeTo->Render();
	RightCursor[0]->Render();
	RightCursor[1]->Render();

	mMiniCube[mRound][mLevel-1]->Render();

	LeftCursor[0]->Render();
	LeftCursor[1]->Render();
	
	for (int i = 0; i < TotalLives && i<MAX_LIVES ; i++)
	{
		mQbertTexture[i]->Render();
	}

}