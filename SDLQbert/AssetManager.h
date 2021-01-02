#pragma once
#include"Graphics.h"
#include<map>
#include<SDL_mixer.h>

class AssetManager
{
public:
	static AssetManager * sInstance;
	map<string, SDL_Texture*> mTexture;
	map<string, SDL_Texture *> mText;
	map<string, TTF_Font *>mFont;
	map<string, Mix_Music *>mMusic;
	map<string, Mix_Chunk *>mSFX;
public:

	static AssetManager * Instance();
	static void Release();

	SDL_Texture * GetTexture(string filename);
	SDL_Texture * GetText(string text, string file, int size,SDL_Color color);

	Mix_Music * GetMusic(string filename);
	Mix_Chunk * GetSFX(string filename);
private:

	AssetManager();
	~AssetManager();

	TTF_Font * GetFont(string filename, int size);
};