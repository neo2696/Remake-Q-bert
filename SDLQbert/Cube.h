#pragma once
#include"InputManager.h"
#include "Texture.h"

class Cube :public GameEntity
{

private:

	int MaxBounce;
	int CurBounce;
	int mRound;

	Texture * mCubeTexture[4][4];

public:

	void Hit();

	int GetBounce();

	void GetRound(int round);



	void SetMAXBounce(int bounce);
public:

	Cube();
	~Cube();

	void Update();

	void Render();

};