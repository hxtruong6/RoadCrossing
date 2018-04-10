#include "CBIRD.h"


CBIRD::~CBIRD()
{
}

void CBIRD::DrawAnimal() {
	GotoXY(mX, mY);
	SetColor(13);
	if (checkPosition(mX, colBoundary - 1)) { cout << mBird[0][0]; }
	if (checkPosition(mX + 1, colBoundary - 1)) { cout << mBird[0][1]; }
	if (checkPosition(mX + 2, colBoundary - 1)) { cout << mBird[0][2]; }

	GotoXY(mX, mY - 1);
	SetColor(14);
	if (checkPosition(mX, colBoundary - 1)) { cout << mBird[1][0]; }
	if (checkPosition(mX + 1, colBoundary - 1)) { cout << mBird[1][1]; }
	if (checkPosition(mX + 2, colBoundary - 1)) { cout << mBird[1][2]; }

	SetColor(7);
}

void CBIRD::Move(int lengthBoundary, int x) {
	CANIMAL::Move(lengthBoundary, x);

	mX -= x;
	if (mX <= 0) mX += lengthBoundary;
}
