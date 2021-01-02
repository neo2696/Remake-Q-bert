#pragma once
#include "Texture.h"
#include<vector>
using namespace std;

class ScoreBoard : public GameEntity
{
private:

	vector<Texture*> mScore;

	SDL_Color mColor;

public:

	ScoreBoard();
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	void SetScore(int score);

	void Render();

private:

	void ClearScore();


};