#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>

using namespace std;
class Graphics
{
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;	

private:
	static Graphics * sInstance;
	static bool sInitialized;

	SDL_Window * window;
	SDL_Surface * BackBuffer;
	SDL_Renderer * renderer;

public:
	static Graphics * Instance();  // Return the static sInstance
	static void Release();			// To release the static memeory allocation
	static bool Initalized();
	
	
	SDL_Texture *  LoadTexture(string path);
	
	SDL_Texture *CreateTextTexture(TTF_Font * font , string path,SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture * tex,SDL_Rect * clip , SDL_Rect * rect=NULL, float angle =0.0f,SDL_RendererFlip flip=SDL_FLIP_NONE);



	void Render();

private:
	Graphics();
	~Graphics();

	bool Init();

};