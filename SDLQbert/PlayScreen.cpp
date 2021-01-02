#include"PlayScreen.h"
PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();

	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mRight = new PlaySideBar();
	mLeftSidebar = new PlayerSideBar();
	
	mEndLabel = new Texture("GAME OVER", "Q-bert Original.ttf", 40, { 230,230,230 });
	mEndLabel->Parent(this);
	mEndLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));


	mLevel = NULL;

	mRight->Parent(this);
	mLeftSidebar->Parent(this);

	mLevelStartDelay = 0;
	mLevelStarted = false;

	mPlayer = NULL;
	mEnemy = NULL;
	for (int i = 0; i < 10; i++)
	{
		balls[i] = NULL;
	}
	power = NULL;
	disk1 = NULL;
	disk2 = NULL;
}

PlayScreen::~PlayScreen()
{

	delete mRight;
	mRight = NULL;

	delete mLeftSidebar;
	mLeftSidebar = NULL;

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mEndLabel;
	mEndLabel = NULL;

	delete mEnemy;
	mEnemy = NULL;

	for (int i = 0; i < 10; i++)
	{
		delete balls[i];
		balls[i] = NULL;
	}

	delete power;
	power = NULL;

	delete disk1;
	disk1 = NULL;

	delete disk2;
	disk2 = NULL;
}

void PlayScreen::StartFirstLevel()
{
	mCurrentRound++;
	if (mCurrentRound > 4)
	{
		mCurrentRound = mCurrentRound % 4;
		mCurrentLevel++;
		if (mCurrentLevel > 2)
		{
			StartNewGame();
		}
	}
	mLevelStarted = true;
	mLevelStartTimer = 0.0f;
	mPlayer->Pos(Vector2(360, 170));
	disk1->Pos(Vector2(210, 356));
	disk2->Pos(Vector2(510, 356));
	disk1->GetRound(mCurrentRound-1);
	disk2->GetRound(mCurrentRound - 1);
	mLevel = new Level(mCurrentLevel, mCurrentRound, mRight, mPlayer,mLeftSidebar,mEnemy,balls,power,disk1,disk2);
}

void PlayScreen::StartNextLevel()
{
	mCurrentRound++;
	if (mCurrentRound > 4)
	{
		mCurrentRound = mCurrentRound % 4;
		mCurrentLevel++;
		if (mCurrentLevel > 2)
		{
			StartNewGame();
		}
	}
	mLevelStarted = true;
	mLevelStartTimer = 0.0f;
	mPlayer->Pos(Vector2(360, 170));
	mLevel->Reset(mCurrentLevel, mCurrentRound);
	mLeftSidebar->SetMiniCube(mCurrentRound-1, mCurrentLevel);

	disk1->Pos(Vector2(210, 356));
	disk2->Pos(Vector2(510, 356));
	disk1->GetRound(mCurrentRound - 1);
	disk2->GetRound(mCurrentRound - 1);

	if (rand() % 2 == 0)
	{
		mEnemy->Pos(Vector2(330, 222));
		mEnemy->ResetCoily(1, 0);
	}
	else
	{
		mEnemy->Pos(Vector2(390, 222));
		mEnemy->ResetCoily(1, 1);
	}
	for (int i = 0; i < 10; i++)
	{
		if (rand() % 2 == 0)
		{
			balls[i]->Pos(Vector2(390, 222));
		}
		else
		{
			balls[i]->Pos(Vector2(330, 222));
		}
	}
	if (mCurrentRound == 2)
	{
		if (rand() % 2 == 0)
		{
			power->Pos(Vector2(390, 222));
		}
		else
		{
			power->Pos(Vector2(330, 222));
		}
	}
}


void PlayScreen::StartNewGame()
{
	//delete mPlayer;
	mPlayer = new Player();
	mPlayer->Pos(Vector2(360,170));
	mPlayer->Active(false);
	
	mAudio->PlayMusic("Game start music.wav",0);
	
	mLeftSidebar->SetPlayerLives(mPlayer->Lives());
	mLeftSidebar->SetPlayerScore(mPlayer->Score());
	mRight->SetHighScore(10000);
	mGameStarted = false;
	mCurrentLevel = 1;
	mCurrentRound = 0;
	mRight->SetLevel(mCurrentLevel, mCurrentRound);
	mLeftSidebar->SetMiniCube(mCurrentRound, mCurrentLevel);
	
	delete disk1;
	delete disk2;
	disk1 = new Disk();
	disk2 = new Disk();
	disk1->Pos(Vector2(210, 356));
	disk2->Pos(Vector2(510, 356));
	disk1->GetRound(mCurrentRound - 1);
	disk2->GetRound(mCurrentRound - 1);
	
	delete mEnemy;
	mEnemy = new Coily();
	delete power;
	power = new GreenBall();
	mEnemy->Active(false);
	for (int i = 0; i < 10; i++)
	{
		delete balls[i];
		balls[i] = new Ball();
		balls[i]->Active(false);
	}
	if (rand() % 2 == 0)
	{
		mEnemy->Pos(Vector2(330, 222));
		mEnemy->ResetCoily(1, 0);
	}
	else
	{
		mEnemy->Pos(Vector2(390, 222));
		mEnemy->ResetCoily(1, 1);
	}
	for (int i = 0; i < 10; i++)
	{
		if (rand() % 2 == 0)
		{
			balls[i]->Pos(Vector2(390, 222));
		}
		else
		{
			balls[i]->Pos(Vector2(330, 222));
		}
	}
	if (mCurrentRound % 2 == 0)
	{
		if (rand() % 2 == 0)
		{
			power->Pos(Vector2(390, 222));
		}
		else
		{
			power->Pos(Vector2(330, 222));
		}
	}
}


void PlayScreen::Update()
{
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay )
			{
				StartFirstLevel();
			}

			if (mPlayer->Lives() == 0)
			{
				mGameOver = true;
				mAudio->PlaySFX("byebye.png");
			}
		}

	}
	else
	{
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}

	if (mGameStarted && mLevelStarted)
	{
		mRight->Update();
		mLeftSidebar->Update();
		mLeftSidebar->SetPlayerScore(mPlayer->Score());
		mLeftSidebar->SetPlayerLives(mPlayer->Lives());
	
		mPlayer->Update();
		disk1->Update();
		disk2->Update();
		mLevel->Update();
		
		if (!mLevel->GameStop())
		{
			mEnemy->Update();
			for (int i = 0; i < 10; i++)
			{
					balls[i]->Update();
			}
		}
		power->Update();
		if (mPlayer->Lives() < 1)
		{
			mGameOver = true;
		}
		if (mLevel->LevelOver())
		{
			SDL_Delay(1000);
			StartNextLevel();
		}
	
	}

}

void PlayScreen::Render()
{
	if (mGameStarted && mLevelStarted)
	{
		mLevel->Render();
	}

	if (mGameOver)
	{
		if (mPlayer->Score() > mRight->GetHighScore())
		{
			mRight->SetHighScore(mPlayer->Score());
		}
		mEndLabel->Render();
	}
}