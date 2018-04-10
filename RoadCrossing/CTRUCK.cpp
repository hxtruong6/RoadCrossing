#include "CTRUCK.h"


CTRUCK::~CTRUCK()
{
}



void CTRUCK::DrawVehicle() {
	GotoXY(mX, mY);
	SetColor(11);
	if (checkPosition(mX, colBoundary - 1)) { cout << mTruck[0][0]; }
	SetColor(6);
	if (checkPosition(mX + 1, colBoundary - 1)) { cout << mTruck[0][1]; }
	if (checkPosition(mX + 2, colBoundary - 1)) { cout << mTruck[0][2]; }

	GotoXY(mX, mY - 1);
	SetColor(13);
	if (checkPosition(mX, colBoundary - 1)) { cout << mTruck[1][0]; }
	if (checkPosition(mX + 1, colBoundary - 1)) { cout << mTruck[1][1]; }
	if (checkPosition(mX + 2, colBoundary - 1)) { cout << mTruck[1][2]; }

	SetColor(7);
}

void CTRUCK::Move(int lengthBoundary, int x) {
	CVEHICLE::Move(lengthBoundary, x);
	mX -= x;
	if (mX <= 0) mX += lengthBoundary;
}


