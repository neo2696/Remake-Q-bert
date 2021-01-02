#include"Level.h"
int XPOS = 0;
int YPOS = 0;
int countCube = 0;
int NumBallsLeft = 10;
bool STOPALL = false;
Level::Level(int level, int round, PlaySideBar * sidebar, Player * player, PlayerSideBar * LEFTBAR, Coily * enemy, Ball * balls[10], GreenBall * power, Disk * disk1, Disk * disk2)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	Right = sidebar;
	Right->SetLevel(level, round);

	
	mBAR = LEFTBAR;

	mLevel = level;
	mRound = round;
	mLevelStarted = false;

	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("Level ", "Q-Bert Original.ttf", 24, { 230,230,230 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));

	mLevelNumber = new ScoreBoard({ 75,75,200 });
	mLevelNumber->SetScore(level);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.65f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));

	mRoundLabel = new Texture("Round  ", "Q-Bert Original.ttf", 24, { 230,230,230 });
	mRoundLabel->Parent(this);
	mRoundLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.51f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mRoundNumber = new ScoreBoard({ 75,75,200 });
	mRoundNumber->SetScore(round);
	mRoundNumber->Parent(this);
	mRoundNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.65f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelOnScreen = 0.0f;
	mLevelOffScreen = 1.0f;

	//Level Entites
	mdisk1 = disk1;
	mdisk2 = disk2;

	disk1->Parent(this);
	disk2->Parent(this);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i+1; j++)
		{
			mCube[i][j] = new Cube();
			mCube[i][j]->Parent(this);
			mCube[i][j]->SetMAXBounce(mLevel);
			mCube[i][j]->GetRound(mRound);
		}
	}

	//Cubes Positioning

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			mCube[i][j]->Pos(Vector2(360 - (i * 30) + (j * 60), 200 +( 52 * i)));
		}
	}

	/*for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			SDL_Log("Cube  %d %d Position is %f %f ",i,j,mCube[i][j]->Pos().x,mCube[i][j]->Pos().y);
		}
	}*/

	mPlayer = player;
	mPlayer->Parent(this);

	mEnemySnake = enemy;
	mEnemySnake->Parent(this);
	for (int i = 0; i < 10; i++)
	{
		mBall[i] = balls[i];
		flag[i] = true;
	}

	mPowerUP = power;
}

Level::~Level()
{
	mTimer = NULL;
	Right = NULL;
	mAudio = NULL;
	mBAR = NULL;

	delete mLevelLabel;
	mLevelLabel = NULL;

	delete mLevelNumber;
	mLevelNumber = NULL;

	delete mRoundLabel;
	mRoundLabel = NULL;

	delete mRoundNumber;
	mRoundNumber = NULL;

	delete mdisk1;
	mdisk1 = NULL;

	delete mdisk2;
	mdisk2 = NULL;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i+1; j++)
		{
			mCube [i][j] = NULL;
		}
	}


	mPlayer = NULL;

	mEnemySnake = NULL;
	for (int i = 0; i < 10; i++)
	{
		mBall[i] = NULL;
	}
	mflag1 = false;

	mPowerUP = NULL;
}

void Level::Reset(int level , int round)
{
	if (mFlagCube)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				mCube[i][j]->SetMAXBounce(level);
				mCube[i][j]->GetRound(round);
				SDL_Log("Cube %d %d Cur Bounce and MAx Bounce are : %d  %d  ", i, j, mCube[i][j]->GetBounce(), level);
			}
		}
		mTimer = Timer::Instance();
		Right->SetLevel(level, round);

		mLevel = level;
		mRound = round;
		mLevelStarted = false;
		mLevelOver = false;
		mLabelTimer = 0.0f;

		mLevelOnScreen = 0.0f;
		mLevelOffScreen = 1.0f;

		mRoundNumber->SetScore(mRound);
		mLevelNumber->SetScore(mLevel);
		countCube = 0;
		mflag1 = false;
		NumBallsLeft = 10;
		for (int i = 0; i < 10; i++)
		{
			flag[i] = true;
		}
		STOPALL = false;
	}
	if (rand() % 2 == 0)
	{
		mEnemySnake->ResetCoily(1, 1);
		mEnemySnake->Pos(Vector2(390, 222));
	}
	else
	{
		mEnemySnake->ResetCoily(1, 0);
		mEnemySnake->Pos(Vector2(330, 222));
	}
	XPOS = 0;
	YPOS = 0;
}

void Level::Collision(Player * player , Cube * box)
{
	if (box->GetBounce() < mLevel)
	{
		box->Hit();
		player->CubeLanded();
	}
}

void Level::StartRound()
{
	mLevelStarted = true;
	mLevelOver = false;
	mFlagCube = false;
}

bool Level::LevelOver()
{
	return mLevelOver;
}

bool Level::GameStop()
{
	return STOPALL;
}

void Level::Update()
{
	if (!mLevelStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer > mLevelOffScreen)
		{
			StartRound();
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
	if (mLevelStarted)
	{
		mEnemySnake->Active(true);
		if (mBall[10 - NumBallsLeft] != NULL)
		{
			mBall[10 - NumBallsLeft]->Active(true);
		}
	}
	mPlayer->SetDeathFlag(0);
	if (countCube == MAX_BOUNCES * mLevel)
	{
		mLevelOver = true;
		mFlagCube = true;
		mPlayer->AddScore(1000 + 250 * (mRound - 1));
	}
	if (NumBallsLeft == 1)
	{
		mflag1 = true;
	}
	if (!STOPALL)
	{
		if (!mflag1)
		{
			if (mBall[10 - NumBallsLeft]->Pos().y > 512)
			{
				flag[10 - NumBallsLeft] = false;
				mBall[10 - NumBallsLeft]->~Ball();
				NumBallsLeft--;
			}
		}
		cout << "Value of NumBallsLeft = %d " << NumBallsLeft << endl;
		if (mPlayer->Lives() > 0)
		{
			if (XPOS != 0 && YPOS != 0)
			{
				mEnemySnake->SendPlayerPos(XPOS, YPOS);
			}
			int CoilyX = mEnemySnake->CoilyAtRow();
			int CoilyY = mEnemySnake->CoilyAtCol();
			SDL_Log("Position of Snake Coily : %f %f", mEnemySnake->Pos().x, mEnemySnake->Pos().y);
			SDL_Log("Snake Coily at Cube : %d %d", CoilyX, CoilyY);
			if ((CoilyX == XPOS && CoilyY == YPOS) || (mPlayer->Pos().x == mBall[10 - NumBallsLeft]->Pos().x  && mPlayer->Pos().y == mBall[10 - NumBallsLeft]->Pos().y))
			{
				mPlayer->WasHit();
				mAudio->PlaySFX("Coily Bite.wav");
				XPOS = 0;
				YPOS = 0;
				mPlayer->Pos(Vector2(360, 170));
				Reset(mLevel, mRound);

			}
		}
	}
		if (mPlayer->Pos().x == mPowerUP->Pos().x  &&  mPlayer->Pos().y == mPowerUP->Pos().y)
		{
			STOPALL = true;
		}
		if (mPlayer->GetFlagsStatus('Q'))
		{
			XPOS = XPOS - 1;
			YPOS = YPOS - 1;
			if (XPOS < 0)
			{
				mPlayer->WentOutofBounds();
				XPOS = 0;
				YPOS = 0;
				mPlayer->Pos(Vector2(360, 170));
				mAudio->PlaySFX("Qbert Over the edge.wav");
				Reset(mLevel, mRound);
			}
		}
		if (mPlayer->GetFlagsStatus('E'))
		{
			XPOS = XPOS - 1;
			if (XPOS < 0)
			{
				mPlayer->WentOutofBounds();
				XPOS = 0;
				YPOS = 0;
				mPlayer->Pos(Vector2(360, 170));
				mAudio->PlaySFX("Qbert Over the edge.wav");
				Reset(mLevel, mRound);
			}
		}
		if (mPlayer->GetFlagsStatus('A'))
		{
			XPOS = XPOS + 1;
			if (XPOS > 6)
			{
				mPlayer->WentOutofBounds();
				XPOS = 0;
				YPOS = 0;
				mPlayer->Pos(Vector2(360, 170));
				mAudio->PlaySFX("Qbert Over the edge.wav");
				Reset(mLevel, mRound);
			}
		}
		if (mPlayer->GetFlagsStatus('D'))
		{
			XPOS = XPOS + 1;
			YPOS = YPOS + 1;
			if (XPOS > 6 || YPOS > 6)
			{
				mPlayer->WentOutofBounds();
				XPOS = 0;
				YPOS = 0;
				mPlayer->Pos(Vector2(360, 170));
				mAudio->PlaySFX("Qbert Over the edge.wav");
				Reset(mLevel, mRound);
			}
		}

		if (mPlayer->GetFlagsStatus('D') || mPlayer->GetFlagsStatus('Q') || mPlayer->GetFlagsStatus('E') || mPlayer->GetFlagsStatus('A'))
		{
			if (mCube[XPOS][YPOS]->GetBounce() != mLevel)
			{
				mPlayer->AddScore(25);
			}
			if (mCube[XPOS][YPOS]->GetBounce() != mLevel)
			{
				countCube++;
			}
			Collision(mPlayer, mCube[XPOS][YPOS]);
		}
}

void Level::Render()
{
	if (!mLevelStarted)
	{
		mLevelLabel->Render();
		mLevelNumber->Render();
		mRoundLabel->Render();
		mRoundNumber->Render();
	}
	else
	{
		Right->Render();
		mBAR->Render();
		
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < i+1; j++)
			{
				mCube[i][j]->Render();
			}
			
		}
		mPlayer->Render();
		mdisk1->Render();
		mdisk2->Render();
		mEnemySnake->Render();
		for (int i = 0; i < 10; i++)
		{
			if (flag[i])
			{
				mBall[i]->Render();
			}
		}
		mPowerUP->Render();
	}
}