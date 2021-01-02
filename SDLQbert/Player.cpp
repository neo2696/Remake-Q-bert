#include"Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mbounce = 0;
	mScore = 0;
	mLives = 3;
	mQbert[0] = new Texture("QBertQ.png");
	mQbert[1] = new Texture("QBertE.png");
	mQbert[2] = new Texture("QBert.png");
	mQbert[3] = new Texture("QBertD.png");
	for (int i = 0; i < 4; i++)
	{
		mQbert[i]->Parent(this);
		mQbert[i]->Pos(VEC2_ZERO);
	}

	MoveSpeed = 10.0f;
	

	mDeath = new Texture("QBert Death.png");
	mDeath->Parent(this);
	mDeath->Pos(VEC2_ZERO);
	mJumpAnimation[2] = new AnimatedTexture("QBert Animation A.png", 0, 0, 30, 63, 2, 35.0f, AnimatedTexture::horizontal);
	mJumpAnimation[0] = new AnimatedTexture("QBert Animation Q.png", 0, 0, 30, 63, 2, 35.0f, AnimatedTexture::horizontal);
	mJumpAnimation[1] = new AnimatedTexture("QBert Animation E.png", 0, 0, 30, 63, 2, 35.0f, AnimatedTexture::horizontal);
	mJumpAnimation[3] = new AnimatedTexture("QBert Animation D.png", 0, 0, 30, 63, 2, 35.0f, AnimatedTexture::horizontal);
	
	for (int i = 0; i < 4; i++)
	{
		mJumpAnimation[i]->Parent(this);
		mJumpAnimation[i]->Pos(VEC2_ZERO);
		mJumpAnimation[i]->WrapMode(AnimatedTexture::once);
	}
	lastkey = 2;
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	for (int i = 0; i < 4; i++)
	{

		delete mQbert[i];
		mQbert[i] = NULL;

	}
	

	delete mDeath;
	mDeath = NULL;

	delete mJumpAnimationA;
	mJumpAnimationA = NULL;
	for (int i = 0; i < 4; i++)
	{

		delete mJumpAnimation[i];
		mJumpAnimation[i] = NULL;

	}

}

void Player::CubeLanded()
{
	mbounce++;
}


void Player::WasHit()
{
	mLives--;
	mdeathflag=true;
}

void Player::SetDeathFlag(bool val)
{
	mdeathflag = val;
}

void Player::WentOutofBounds()
{
	mLives--;
}

void Player::HandleMovement()
{
	
	if (mInput->KeyPressed(SDL_SCANCODE_Q))
	{
		mAnimating = true;
		flags[0] = true;
		lastkey = 0;
		Translate(Vector2(-30, -52));
		mAudio->PlaySFX("Hop.wav");
		mJumpAnimation[0]->ResetAnimation();

	}
	else if (mInput->KeyPressed(SDL_SCANCODE_E))
	{
		mAnimating = true;
		lastkey = 1;
		flags[1] = true;
		Translate(Vector2(30, -52));
		mAudio->PlaySFX("Hop.wav");
		mJumpAnimation[1]->ResetAnimation();
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_A))
	{
		mAnimating = true;
		lastkey = 2;
		flags[2] = true;
		Translate(Vector2(-30, 52));
		mAudio->PlaySFX("Hop.wav");
		mJumpAnimation[2]->ResetAnimation();
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_D))
	{
		mAnimating = true;
		lastkey = 3;
		flags[3] = true;
		Translate(Vector2(30, 52));
		mAudio->PlaySFX("Hop.wav");
		mJumpAnimation[3]->ResetAnimation();
	}

}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

bool Player::GetFlagsStatus(char ch)
{
	if (ch == 'Q')
	{
		return flags[0];
	}
	else if (ch == 'E')
	{
		return flags[1];
	}
	else if (ch == 'A')
	{
		return flags[2];
	}
	else if(ch == 'D')
	{
		return flags[3];
	}
}


int Player::Bounce()
{
	return mbounce;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

void Player::Update()
{
	for (int i = 0; i < 4; i++)
	{
		flags[i] = false;
	}
	mAnimating = false;
	if (IsAnimating())
	{
		for (int i = 0; i < 4; i++)
		{
			mJumpAnimation[i]->Update();
			//mAnimating = mJumpAnimation[i]->IsAnimating();
		}
		
	}
	else
	{
		if (Active())
		{
			HandleMovement();
		}
	}
	
}

void Player::Render()
{
	if (mVisible)
	{
		if (IsAnimating())
		{
			mJumpAnimation[lastkey]->Render();
		}
		else
		{
			if (mdeathflag)
			{
				mDeath->Render();
			}
			mQbert[lastkey]->Render();
			
		}
	}
}