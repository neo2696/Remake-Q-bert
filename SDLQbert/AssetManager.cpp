#include"AssetManager.h"

AssetManager * AssetManager::sInstance = NULL;
AssetManager * AssetManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager ::~AssetManager()
{
	for (auto tex : mTexture)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}

	mTexture.clear();

	for (auto text : mText)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	mText.clear();

	for (auto font : mFont)
	{
		if (font.second != NULL)

		{
			TTF_CloseFont(font.second);
		}
	}

	mFont.clear();

	for (auto music : mMusic)
	{
		if (music.second != NULL)

		{
			Mix_FreeMusic(music.second);
		}
	}

	mMusic.clear();

	for (auto sfx : mSFX)
	{
		if (sfx.second != NULL)

		{
			Mix_FreeChunk(sfx.second);
		}
	}

	mSFX.clear();

}

SDL_Texture * AssetManager::GetTexture(string filename)
{
	string path = SDL_GetBasePath();
	path.append("Assets/" + filename);

	if (mTexture[path] == nullptr)
		mTexture[path] = Graphics::Instance()->LoadTexture(path);

	return mTexture[path];
}

TTF_Font * AssetManager::GetFont(string filename, int size)
{
	string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);
	
	string key = fullpath + (char)size;
	cout << fullpath << " " << key << endl;
	cout << mFont[key] << endl;
	if (mFont[key] == NULL)
	{
		mFont[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (mFont[key] == NULL)
		{
			SDL_Log("Font Loading Error : Font -%s Error-%s\n", filename.c_str(), TTF_GetError());
		}
	}

	return mFont[key];
}

SDL_Texture * AssetManager::GetText(string text, string filename, int size,SDL_Color color)
{
	TTF_Font * font = GetFont(filename, size);
	if (font == NULL)
	{
		SDL_Log("Font not open %s\n",TTF_GetError());
	}
	string key = text + filename + (char)size;

	if (mText[key] == NULL)
	{
		mText[key] = Graphics::Instance()->CreateTextTexture(font, text,color);
	}

	return mText[key];
}

Mix_Music * AssetManager::GetMusic(string filename)
{
	string path = SDL_GetBasePath();
	path.append("Assets/" + filename);
	if (mMusic[path] == NULL)
	{
		mMusic[path] = Mix_LoadMUS(path.c_str());
		if (mMusic[path] == NULL)
		{
			SDL_Log("Music Loading Error : File %s Error %s", filename.c_str(), Mix_GetError());
		}
	}

	return mMusic[path];
}

Mix_Chunk * AssetManager::GetSFX(string filename)
{
	string path = SDL_GetBasePath();
	path.append("Assets/" +filename);
	if (mSFX[path] == NULL)
	{
		mSFX[path] = Mix_LoadWAV(path.c_str());
		if (mSFX[path] == NULL)
		{
			SDL_Log("SFX Loading Error : File %s Error %s", filename.c_str(), Mix_GetError());
		}
	}

	return mSFX[path];

} 