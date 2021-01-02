#include "StartScreen.h"

StartScreen ::StartScreen()
{
	mTImer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top Bar Entities
	mTopBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 50.0f);
	Ultra = new Texture("ULTRA ", "Q-bert Original.ttf", 40, { 255,0,0 });
	mGameTM= new Texture("Games TM ", "Q-bert Original.ttf", 20, { 230,230,230 });

	Ultra->Parent(mTopBar);
	mGameTM->Parent(mTopBar);
	
	Ultra->Pos(VEC2_ZERO);
	mGameTM->Pos(Vector2(40.0f,30.0f));

	mTopBar->Parent(this);

	//Logo Entities
	mLogo = new Texture("Qbert Logo.png");

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.35f));

	mLogo->Parent(this);

	//Play Mode Entities

	mPlayModes = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT  * 0.55f);
	mONE = new Texture(" 1", "Q-bert Original.ttf", 20, { 255,0,0 });
	mTWO = new Texture(" 2", "Q-bert Original.ttf", 20, { 255,0,0 });
	mOnePlayerMode = new Texture(" Player ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mTwoPlayerMode= new Texture(" Players ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mCursor = new Texture("Cursor.png");


	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mONE->Parent(mPlayModes);
	mTWO->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mONE->Pos(Vector2(-90.0f, -26.0f));
	mTWO->Pos(Vector2(-90.0f, 24.0f));
	mOnePlayerMode->Pos(Vector2(0.0f, -25.0f));
	mTwoPlayerMode->Pos(Vector2(10.0f, 25.0f));
	mCursor->Pos(Vector2(-105.0f, -23.0f));


	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 50.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities

	mBotBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT  * 0.7f);
	mTMandDate = new Texture("TM AND  1989", "Q-bert Original.ttf", 20, { 230,230,230 });
	mKonami =  new Texture("KONAMI INDUSTRY  CO . , LTD. ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mLicense = new Texture("LICENSED BY ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mNintendo = new Texture("NINTENDO OF AMERICA  INC. ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mUltraGames = new Texture("ULTRA GAMES  IS A REGISTERED ", "Q-bert Original.ttf", 20, { 230,230,230 });
	mTrademark = new Texture("TRADEMARK OF ULTRA SOFTWARE", "Q-bert Original.ttf", 20, { 230,230,230 });
	mCorporation = new Texture("CORPORATION .", "Q-bert Original.ttf", 20, { 230,230,230 });

	mTMandDate->Parent(mBotBar);
	mKonami->Parent(mBotBar);
	mLicense->Parent(mBotBar);
	mNintendo->Parent(mBotBar);
	mUltraGames->Parent(mBotBar);
	mTrademark->Parent(mBotBar);
	mCorporation->Parent(mBotBar);

	mTMandDate->Pos(Vector2(0.0f, -10.0f));
	mKonami->Pos(Vector2(0.0f, 10.0f));
	mLicense->Pos(Vector2(0.0f,30.0f));
	mNintendo->Pos(Vector2(0.0f, 50.0f));
	mUltraGames->Pos(Vector2(0.0f, 100.0f));
	mTrademark->Pos(Vector2(0.0f, 120.0f));
	mCorporation->Pos(Vector2(0.0f, 140.0f));
	mBotBar->Parent(this);

	//Screen Animation Variables
	ResetAnimation();

	

}

StartScreen :: ~StartScreen()
{
	//Freeing TopBAr Entites
	delete mTopBar;
	mTopBar = NULL;
	
	delete Ultra;
	Ultra = NULL;

	delete mGameTM;
	mGameTM = NULL;

	//Freeing Logo Entites
	delete mLogo;
	mLogo = NULL;

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;

	delete mOnePlayerMode;
	mOnePlayerMode = NULL;

	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;

	delete mONE;
	mONE = NULL;

	delete mTWO;
	mTWO = NULL;

	delete mCursor;
	mCursor = NULL;

	// Freeing BotBar Entities
	delete mBotBar;
	mBotBar = NULL;

	delete mTMandDate;
	mTMandDate = NULL;

	delete mKonami;
	mKonami = NULL;

	delete mLicense;
	mLicense = NULL;

	delete mNintendo;
	mNintendo = NULL;

	delete mUltraGames;
	mUltraGames = NULL;

	delete mTrademark;
	mTrademark = NULL;

	delete mCorporation;
	mCorporation = NULL;
}

void StartScreen::ResetAnimation()
{
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int mode)
{
	mSelectedMode += mode;
	if (mSelectedMode < 0)
	{
		mSelectedMode = 1;
	}
	else if(mSelectedMode > 1)
	{
		mSelectedMode = 0;
	}

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}
void StartScreen::Render()
{
	Ultra->Render();
	mGameTM->Render();

	mLogo->Render();

	mONE->Render();
	mTWO->Render();
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mTMandDate->Render();
	mKonami->Render();
	mLicense->Render();
	mNintendo->Render();
	mUltraGames->Render();
	mTrademark->Render();
	mCorporation->Render();

}

void StartScreen::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTImer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
		}
	}
	else
	{
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
			ChangeSelectedMode(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP))
			ChangeSelectedMode(-1);
	}
}