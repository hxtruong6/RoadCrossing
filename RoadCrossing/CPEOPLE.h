#pragma once
#include "Console.h"
#include "CVEHICLE.h"

class CPEOPLE {
	string mPeople[2];
	int mX, mY;
	bool mState; //Trạng thái sống chết

	void mDelete(); // delete last postion of people before move

public:
	CPEOPLE(int x = colBoundary / 2, int y = rowBoundary - 1, int state = true);
	~CPEOPLE();
	void Up();
	void Left();
	void Right();
	void Down();
	bool IsImpact();
	bool IsFinish();
	bool IsDead();

	void DrawPeople();
	void animationDie();
	void saveGame(ofstream& fo);
};
