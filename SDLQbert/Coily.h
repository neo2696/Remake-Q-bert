#pragma once
#include"AnimatedTexture.h"
#include"AudioManager.h"
#include"Player.h"
#include"MathHelper.h"

class Coily :public GameEntity
{

private:

	Texture * mCoilyTexture[2][4];
	Timer * mTimer;
	AudioManager * mAudio;
	float MoveSpeed;
	int X;
	int Y;
	int row;
	int col;
	bool mMove;
	int DiffCol;
	int DiffRow;
	bool  mflags[4];
	Vector2 MinMoveBounds[7];
	Vector2 MaxMoveBounds[7];

private:

	void HandleMovement();
	bool IsMoving();
public:

	Coily();
	~Coily();

	int CoilyAtRow();
	int CoilyAtCol();

	void ResetCoily(int r, int c);
	void SendPlayerPos(int xpos,int ypos);
	void Update();

	void Render();
};