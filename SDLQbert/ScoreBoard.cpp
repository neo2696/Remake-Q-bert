#include"ScoreBoard.h"

ScoreBoard::ScoreBoard()
	:ScoreBoard({ 255,165,0 })
{
	
}

ScoreBoard::ScoreBoard(SDL_Color color)
{
	mColor = color;
	SetScore(0);
}

ScoreBoard ::~ScoreBoard()
{
	ClearScore();

}

void ScoreBoard::ClearScore()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void ScoreBoard::SetScore(int score)
{
	ClearScore();
	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "Q-bert Original.ttf", 24, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-24 * i, 0));
		}
	}
	else
	{
		string str = to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			mScore.push_back(new Texture(str.substr(i, 1), "Q-bert Original.ttf", 24, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-24 * (lastIndex-i), 0));
		}
	}
}

void ScoreBoard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}

}