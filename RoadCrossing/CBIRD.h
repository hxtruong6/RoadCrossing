#pragma once
#include "CANIMAL.h"

class CBIRD:public CANIMAL
{
	string mBird[2];
public:
	CBIRD(int x, int y):CANIMAL(x,y) {
		mBird[0] = " " + string(1, 223) + " ";
		mBird[1] = string(1, 220) + " " + string(1, 220);
	}
	~CBIRD();

	void DrawAnimal() override;

	void Move(int lengthBoundary, int x=1);
};
