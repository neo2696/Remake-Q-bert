#include"Cube.h"

Cube::Cube()
{
	//Texture at 1 Round
	mCubeTexture[0][0]= new Texture("cube1.png");
	mCubeTexture[0][1] = new Texture("cube12.png");
	mCubeTexture[0][2] = new Texture("cube13.png");

	//Texture at 2 Round
	mCubeTexture[1][0] = new Texture("cube2.png");
	mCubeTexture[1][1] = new Texture("cube21.png");
	mCubeTexture[1][2] = new Texture("cube22.png");

	//Texture at 3 Round
	mCubeTexture[2][0] = new Texture("cube3.png");
	mCubeTexture[2][1] = new Texture("cube31.png");
	mCubeTexture[2][2] = new Texture("cube32.png");

	//Texture at 4 Round
	mCubeTexture[3][0] = new Texture("cube4.png");
	mCubeTexture[3][1] = new Texture("cube41.png");
	mCubeTexture[3][2] = new Texture("cube42.png");




	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mCubeTexture[i][j]->Parent(this);
		}
	}

}

Cube ::~Cube()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete  mCubeTexture[i][j];
			mCubeTexture[i][j] = NULL;
		}
	}
}

void Cube::SetMAXBounce(int bounce)
{
	CurBounce = 0;
	MaxBounce = bounce;
	
}

void Cube::GetRound(int round)
{
	mRound = round;
}

void Cube::Hit()
{
	CurBounce++;
	
}

int Cube::GetBounce()
{
	return CurBounce;
}

void Cube::Update()
{
	
}

void Cube::Render()
{
	mCubeTexture[mRound-1][CurBounce]->Render();
}