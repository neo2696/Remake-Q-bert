#include"InputManager.h"

InputManager * InputManager::sInstance = NULL;

InputManager * InputManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new InputManager();
	
	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

InputManager::InputManager()
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeyBoardState = new Uint8[mKeyLength];
	memcpy(mPrevKeyBoardState, mKeyboardState, mKeyLength);
}

InputManager ::~InputManager()
{
	delete[] mPrevKeyBoardState;
	mPrevKeyBoardState = NULL;


}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scancode)
{
	return !mPrevKeyBoardState[scancode] && mKeyboardState[scancode];
}

bool InputManager::KeyReleased(SDL_Scancode scancode)
{
	return mPrevKeyBoardState[scancode] && !mKeyboardState[scancode];
}

Vector2 InputManager::MousePos()
{
	return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;
	switch (button)
	{
	case left:
	{
		mask = SDL_BUTTON_LMASK;
		break;
	}
	case right:
	{
		mask = SDL_BUTTON_RMASK;
		break;
	}
	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mMouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;
	switch (button)
	{
	case left:
	{
		mask = SDL_BUTTON_LMASK;
		break;
	}
	case right:
	{
		mask = SDL_BUTTON_RMASK;
		break;
	}
	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(mPrevMouseState & mask ) &&  (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;
	switch (button)
	{
	case left:
	{
		mask = SDL_BUTTON_LMASK;
		break;
	}
	case right:
	{
		mask = SDL_BUTTON_RMASK;
		break;
	}
	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mPrevMouseState & mask) && !(mMouseState & mask);
}

void InputManager::Update()
{
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);

}

void InputManager::UpdatePrevInput()
{
	memcpy(mPrevKeyBoardState, mKeyboardState, mKeyLength);
	mPrevMouseState = mMouseState;
}
