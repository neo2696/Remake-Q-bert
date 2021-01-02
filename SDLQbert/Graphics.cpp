#include"Graphics.h"

Graphics * Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics * Graphics::Instance()
{
	if (sInstance == NULL)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = NULL;
	sInitialized = false;

}

bool Graphics::Initalized()
{
	return sInitialized;
}

Graphics::Graphics()
{
	BackBuffer = NULL;
	sInitialized = Init();
}

Graphics :: ~Graphics()
{
	SDL_DestroyWindow(window);
	window = NULL;
	
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL Initalization Error : %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Q*BERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		SDL_Log("Window Creation Error : %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		SDL_Log("Renderer Creation Error : %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	int flags = IMG_INIT_PNG;

	if (!(IMG_Init(flags) & flags))
	{
		SDL_Log("Image Initializtion Error :%s\n", IMG_GetError());
		return false;
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("TTF Initialization Error : %s\n", TTF_GetError());
		return false;
	}

	BackBuffer = SDL_GetWindowSurface(window);

	return true;
}

SDL_Texture * Graphics::LoadTexture(string path)
{
	SDL_Texture *tex = NULL;
	
	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		SDL_Log("Image Load Error : Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL)
	{
		SDL_Log("Create Texture Error :%s\n", SDL_GetError());
		return tex;
	}
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture * Graphics::CreateTextTexture (TTF_Font * font, string text,SDL_Color color)
{
	SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		SDL_Log("Text Render Error : %s\n", TTF_GetError());
		return NULL;
	}

	SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surface);

	if (tex == NULL)
	{
		SDL_Log("Text texture Creation Error : %s\n", SDL_GetError());
		return NULL;
	
	}

	SDL_FreeSurface(surface);
	
	return tex;

}
void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(renderer);
}

void Graphics::DrawTexture(SDL_Texture * tex,SDL_Rect * clip , SDL_Rect * rect, float angle , SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, tex,clip,rect,angle,NULL,flip);
}

void Graphics::Render()
{
	SDL_RenderPresent(renderer);
	//SDL_UpdateWindowSurface(window);
}