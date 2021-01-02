#pragma once

#include "AudioManager.h"
#include "ScreenManager.h"
class GameManager
{
private:
	static GameManager* sInstance;

	const int FRAME_RATE = 60;
	
	bool mQuit;
	Graphics * mGraphics;
	Timer * mTimer;
	SDL_Event mEvents;

	

	AssetManager * mAssetMgr;
	InputManager * mInputMgr;
	AudioManager * mAudioMgr;
	ScreenManager * mScreenMgr;

public:

	static GameManager * Instance();
	static void Release();

	void Run();

private:
	
	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();
};