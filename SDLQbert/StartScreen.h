#pragma once
#include"AnimatedTexture.h"
#include"InputManager.h"



class StartScreen : public GameEntity
{
private:

	Timer * mTImer;
	InputManager * mInput;

	//Top Bar Entities	
	GameEntity * mTopBar;
	Texture * mGameTM;
	Texture * Ultra;


	//Logo Entities
	Texture * mLogo;

	//Play Mode Entities
	GameEntity * mPlayModes;
	Texture * mONE;
	Texture * mTWO;
	Texture * mOnePlayerMode;
	Texture * mTwoPlayerMode;
	Texture * mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	//Bottom Bar Entities
	GameEntity * mBotBar;
	Texture * mTMandDate;
	Texture * mKonami;
	Texture * mLicense;
	Texture * mNintendo;
	Texture * mUltraGames;
	Texture * mTrademark;
	Texture * mCorporation;

	//Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;


public:

	StartScreen();
	~StartScreen();

	void ResetAnimation();

	int SelectedMode();

	void ChangeSelectedMode(int mode);

	void Update();

	void Render();

};