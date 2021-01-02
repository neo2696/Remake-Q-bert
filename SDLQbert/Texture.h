#pragma once
#include"GameEntity.h"
#include"AssetManager.h"

class Texture:public GameEntity
{
protected:
	SDL_Texture * mTex;
	Graphics * mGraphics;

	int mWidth;
	int mHeight; 

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

public:
	Texture(string path);
	Texture(string path, int x, int y, int w, int h);
	Texture(string text, string fontpath, int size,SDL_Color color);
	~Texture();

	virtual void Render(); 

};