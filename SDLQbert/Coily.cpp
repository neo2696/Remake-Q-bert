#include"Coily.h"
int I = 1;
Coily::Coily()
{

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();


	mCoilyTexture[0][0] = new Texture("Coily1.png");
	mCoilyTexture[1][0] = new Texture("Coily20.png");
	mCoilyTexture[1][1] = new Texture("Coily21.png");
	mCoilyTexture[1][2] = new Texture("Coily22.png");
	mCoilyTexture[1][3] = new Texture("Coily23.png");
	mCoilyTexture[0][0]->Parent(this);
	for (int i = 0; i < 4; i++)
	{
		mCoilyTexture[1][i]->Parent(this);
		mCoilyTexture[1][i]->Pos(VEC2_ZERO);

	}

	mCoilyTexture[0][0]->Pos(VEC2_ZERO);
	MoveSpeed = 60.0f;
	row = 1;
	col = 0;
	mMove = false;
	for (int i = 0; i < 7; i++)
	{
		MinMoveBounds[i].x = 330 - i*30;
		MinMoveBounds[i].y = 200 + i*52;
		MaxMoveBounds[i].x = 390 + i*30;
		MaxMoveBounds[i].y = 252 + i *52;
	}
}

Coily::~Coily()
{
	mTimer = NULL;
	mAudio = NULL;

	delete mCoilyTexture[0][0];
	mCoilyTexture[0][0] = NULL;

	for (int i = 0; i < 4; i++)
	{
		delete mCoilyTexture[1][i];
		mCoilyTexture[1][i] = NULL;
	}
}

void Coily::SendPlayerPos(int xpos,int ypos)
{
	X = xpos;
	Y = ypos;
}

int  Coily:: CoilyAtRow()
{
	return row;
}

int  Coily::CoilyAtCol()
{
	return col;
}

void Coily::ResetCoily(int r, int c)
{
	row = r;
	col = c;
	mMove = false;
}

bool Coily::IsMoving()
{
	return mMove;
}

void Coily::HandleMovement()
{
	for (int i = 0; i < 4; i++)
	{
		mflags[i] = false;
	}
	if (row != 6 && !mMove)
	{
		
		if (rand() % 2 == 0)
		{
			Translate(Vector2(-30, 52) );
			
			row+=1;
		}
		else
		{
			Translate(Vector2(30, 52));
			
			row+=1;
			col+=1;
		}
	}
	else
	{
		mMove= true;
		DiffCol = (Y - col);
		DiffRow = (X - row);
		if (DiffRow > 0)
		{
			if (DiffCol < 0)
			{
				row++;
				if (row <= 6)
				{
					Translate(Vector2(-30, 52));
					
					mflags[2] = true;
				}
				else
				{
					row = 6;
				}
			}
			else if (DiffCol > 0)
			{
				row++;
				col++;
				if (row <= 6 && col <= 6)
				{
					Translate(Vector2(30, 52));
					
					mflags[3] = true;
				}
				else
				{
					row = 6;
					col = 6;
				}
			}
		
		}
		else if (DiffRow < 0)
		{
			if (DiffCol > 0)
			{
				row--;
				if (row >= 0)
				{
					Translate(Vector2(30, -52));
					
					mflags[1] = true;
				}
				else
				{
					row = 0;
				}
			}
			else if(DiffCol < 0)
			{
				row--;
				col--;
				if (row >= 0 && col >= 0)
				{
					Translate(Vector2(-30, -52));
					
					mflags[0] = true;
				}
				else
				{
					row = 0;
					col = 0;
				}
			}
		}
		if (DiffRow == 0 && DiffCol > 0)
		{
			if (rand() % 2 == 0)
			{
				row--;
				if (row >= 0)
				{
					Translate(Vector2(30, -52));
					
					mflags[1] = true;
				}
				else
				{
					row = 0;
				}
			}
			else
			{
				row++;
				col++;
				if (row <= 6 && col <= 6)
				{
					Translate(Vector2(30, 52));
					
					mflags[3] = true;
				}
				else
				{
					row = 6;
					col = 6;
				}
			}

		}
		else if (DiffRow == 0 && DiffCol < 0)
		{
			if (rand() % 2 == 0)
			{
				row--;
				col--;
				if (row >= 0 && col >= 0)
				{
					Translate(Vector2(-30, -52));
					
					mflags[0] = true;
				}
				else
				{
					row = 0;
					col = 0;
				}
			}
			else
			{
				row++;
				if (row <= 6)
				{
					Translate(Vector2(-30, 52));
					
					mflags[2] = true;
				}
				else
				{
					row = 6;
				}
			}

		}
		else if(DiffRow >0 && DiffCol == 0)
		{
			row++;
			if (row <= 6)
			{
				Translate(Vector2(-30, 52));
				
				mflags[2] = true;
			}
			else
			{
				row = 6;
			}
		}
		else if (DiffRow < 0 && DiffCol == 0)
		{
			row--;
			if (row >= 0)
			{
				Translate(Vector2(30, -52));
				
				mflags[1] = true;
			}
			else
			{
				row = 0;
			}
		}
		else
		{

		}
	}
/*	Vector2 position = Pos(local);
	for (int i = 0; i < 7; i++)
	{
		if (row == i)
		{
			if (position.x < MinMoveBounds->x)
			{
				position.x = MinMoveBounds->x;
			}
			else if (position.x > MaxMoveBounds->x)
			{
				position.x = MaxMoveBounds->x;
			}
			else if (position.y > MaxMoveBounds->y)
			{
				position.y= MaxMoveBounds->y;
			}
			else if (position.y < MaxMoveBounds->y)
			{
				position.y = MaxMoveBounds->y;
			}
		}
	}
	Pos(position);*/
		
}

void Coily::Update()
{
	I++;
	if (I % 30  == 0)
	{
		
		if (Active())
		{
			HandleMovement();
		}
	}
}

void Coily::Render()
{

	if (mMove)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mflags[i])
				mCoilyTexture[mMove][i]->Render();
		}
	}
	else
	{
		mCoilyTexture[mMove][0]->Render();
	}
}