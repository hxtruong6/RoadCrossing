#include "CDINAUSOR.h"


CDINAUSOR::~CDINAUSOR()
{
}

void CDINAUSOR::DrawAnimal() {
	GotoXY(mX, mY);
	SetColor(6);
	if (checkPosition(mX, colBoundary - 1)) cout << mDinausor[0][0];
	SetColor(3);
	if (checkPosition(mX + 1, colBoundary - 1)) cout << mDinausor[0][1];
	if (checkPosition(mX + 2, colBoundary - 1)) cout << mDinausor[0][2];

	GotoXY(mX, mY - 1);
	SetColor(11); 
	if (checkPosition(mX, colBoundary - 1)) cout << mDinausor[1][0];
	if (checkPosition(mX + 1, colBoundary - 1)) cout << mDinausor[1][1];
	if (checkPosition(mX + 2, colBoundary - 1)) cout << mDinausor[1][2];

	SetColor(7);
}

void CDINAUSOR::Move(int lengthBoundary, int x) {
	CANIMAL::Move(lengthBoundary, x);
	mX = (mX + x) % lengthBoundary;
	if (mX == 0) mX = lengthBoundary;
}
