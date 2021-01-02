#include"GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;

	mActive = true;
	mParent = NULL;

	mScale = VEC2_ONE;
}

GameEntity ::~GameEntity()
{
	mParent = NULL;
}

void GameEntity::Pos(Vector2 Pos)
{
	mPos = Pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	if (space == local || mParent == NULL)
		return mPos;

	Vector2 parentScale = mParent->Scale(world);
	Vector2 lval = Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y);
	Vector2 rotPos = RotateVector(lval, mParent->Rotation(local));

	return mParent->Pos(world) + rotPos;
}

void GameEntity::Rotation(float r)
{
	mRotation = r;
	if (mRotation > 360.0f)
	{
		mRotation -= 360.0f;
	}
	

}

float GameEntity::Rotation(SPACE space)
{
	if (space == local || mParent == NULL)
		return mRotation;
	
	return mParent->Rotation(world) + mRotation;
}

void GameEntity::Scale(Vector2 scale)
{
	mScale = scale;
}

Vector2 GameEntity::Scale(SPACE space)
{
	if (space == local || mParent == NULL)
		return mScale;

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;
	
	return scale;
}

void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::Active()
{
	return mActive;
}

void GameEntity::Parent(GameEntity * parent)
{
	if (parent == NULL)
	{
		mPos = Pos(world);
		mRotation = Rotation(world);
		mScale = Scale(world);
	}
	else
	{
		if (mParent != NULL)
		{
			Parent(NULL);
		}

		Vector2	parentScale = parent->Scale(world);
		Vector2 lval = Pos(world) - parent->Pos(world);
		mPos = RotateVector(lval, -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		mRotation -= parent->Rotation(world);

		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}
	mParent = parent;

}

GameEntity * GameEntity::Parent()
{
	return mParent;
}

void GameEntity::Translate(Vector2 vec)
{
	mPos += vec;
}

void GameEntity::Rotate(float amount)
{
	mRotation += amount;
}
void  GameEntity::Update()
{

}

void GameEntity::Render()
{

}