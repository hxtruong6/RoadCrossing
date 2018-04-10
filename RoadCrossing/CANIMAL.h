#pragma once
#include "Console.h"
#include <iostream>
#include <string>

using namespace std;

class CANIMAL
{
private:
	void mDelete();
protected:
	int mX, mY;
	bool checkPosition(int x, int boundary);
public:
	CANIMAL(int x, int y) :mX(x), mY(y) {}
	virtual ~CANIMAL();

	virtual void Move(int lengthBoundary, int x = 1);
	virtual void DrawAnimal() = 0;
	void saveGame(ofstream& fo);
};

