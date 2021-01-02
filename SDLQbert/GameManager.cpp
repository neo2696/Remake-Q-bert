#include"GameManager.h"

GameManager * GameManager::sInstance = NULL;
Texture * mTex2;
GameManager * GameManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new GameManager();
	return sInstance;

}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;

}

GameManager::GameManager()
{
	mQuit = false;
	mGraphics = Graphics::Instance();
	
	if (!Graphics::Initalized())
		mQuit = true;


	mAssetMgr = AssetManager::Instance();

	mInputMgr = InputManager::Instance();

	mAudioMgr = AudioManager::Instance();

	mTimer = Timer::Instance();

	mScreenMgr = ScreenManager::Instance();

}

GameManager::~GameManager()
{
	AudioManager::Release();
	mAudioMgr = NULL;

	AssetManager::Release();
	mAssetMgr = NULL;
	
	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputMgr = NULL;

	Timer::Release();
	mTimer = NULL;

	ScreenManager:: Release();
	mScreenMgr = NULL;

}

void GameManager::EarlyUpdate()
{
	mInputMgr->Update();

}

void GameManager::Update()
{

	mScreenMgr->Update();
	
}
void GameManager::LateUpdate()
{

	mInputMgr->UpdatePrevInput();

	mTimer->Reset();

}
void GameManager::Render()
{
	mGraphics->ClearBackBuffer();


	mScreenMgr->Render();
	

	
	mGraphics->Render();

}
void GameManager::Run()
{

	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
			 
			
		}
		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();

			Update();  // Updating Objects 

			LateUpdate();   // Used for Colllsion Detection and Physics

			Render();
			
			
		}
	}
}