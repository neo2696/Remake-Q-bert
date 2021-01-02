#include"Disk.h"

Disk::Disk()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mDiskTex[0] = new AnimatedTexture("DiskTexRound1.png", 0, 0, 30, 30, 4,1.0f, AnimatedTexture::horizontal);
	mDiskTex[1] = new AnimatedTexture("DiskTexRound2.png", 0, 0, 30, 30, 4, 1.0f, AnimatedTexture::horizontal);
	mDiskTex[2] = new AnimatedTexture("DiskTexRound3.png", 0, 0, 30, 30, 4, 1.0f, AnimatedTexture::horizontal);
	mDiskTex[3] = new AnimatedTexture("DiskTexRound4.png", 0, 0, 30, 30, 4, 1.0f, AnimatedTexture::horizontal);


	for (int i = 0; i < 4; i++)
	{
		mDiskTex[i]->Parent(this);
		mDiskTex[i]->Pos(VEC2_ZERO);
	}

	mAnimating = true;
}

Disk::~Disk()
{
	mTimer = NULL;
	mAudio = NULL;
	for (int i = 0; i < 4; i++)
	{
		delete mDiskTex[i];
		mDiskTex[i] = NULL;
	}
}

void Disk::SetAnimating(bool val)
{
	mAnimating = val;
}

void Disk::GetRound(int r)
{
	roundnum = r;

}

bool Disk::IsAnimating()
{
	return mAnimating;
}

void Disk ::Update()
{
	if (IsAnimating())
	{
		mDiskTex[roundnum]->Update();
	}
}

void Disk::Render()
{
	if (IsAnimating())
	{
		mDiskTex[roundnum]->Render();
	}
}

