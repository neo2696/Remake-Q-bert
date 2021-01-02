#pragma once
#include<SDL.h>
#include<string.h>
#include"MathHelper.h"
class InputManager
{

public:
	enum MOUSE_BUTTONS { left=0,right , middle ,back , forward};
private:
	
	static InputManager * sInstance;

	Uint8 * mPrevKeyBoardState;

	const Uint8 * mKeyboardState;
	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;
	
	int mMouseXPos;
	int mMouseYPos;

public:

	static InputManager * Instance();
	static void Release();


	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTONS button);
	bool MouseButtonPressed(MOUSE_BUTTONS button);
	bool MouseButtonReleased(MOUSE_BUTTONS button);
	
	Vector2 MousePos();

	void Update();
	void UpdatePrevInput();

private:
	InputManager();
	~InputManager();
};