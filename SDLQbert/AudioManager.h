#pragma once
#include"AssetManager.h"

class AudioManager
{
private:

	static AudioManager * sInstance;

	AssetManager * mAssetMgr;

public:

	static AudioManager * Instance();
	static void Release();

	void PlayMusic(string filename, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(string filename, int loops = 0,int channel = 0);

private:

	AudioManager();
	~AudioManager();
	 
};