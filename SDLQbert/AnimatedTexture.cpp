#include"AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(string filename, int x, int y, int w, int h, int framecount, float animationspeed, ANIM_DIR animationdir)
	:Texture(filename, x, y, w, h)
{
	mTimer = Timer::Instance();

	mStartx = x;
	mStarty = y;

	mFrameCount = framecount;
	mAnimationSpeed = animationspeed;
	mTimerPerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationdir;

	mAnimationDone = false;

	mWrapMode = loop;
}
	
AnimatedTexture ::~AnimatedTexture()
{

}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void AnimatedTexture::ResetAnimation()
{
	mAnimationTimer = 0.0f;
	mAnimationDone = false;
}

bool AnimatedTexture::IsAnimating()
{
	return !mAnimationDone;
}
void AnimatedTexture::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == loop)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimerPerFrame;
			}
		}
		if (mAnimationDirection == horizontal)
		{
			mClipRect.x = mStartx + (int)(mAnimationTimer / mTimerPerFrame) * mWidth;
		}
		else
		{
			mClipRect.y = mStarty + (int)(mAnimationTimer / mTimerPerFrame) * mHeight;
		}
	}
}