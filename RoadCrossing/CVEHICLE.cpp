#include "CVEHICLE.h"
#include "Console.h"


void CVEHICLE::mDelete() {
	GotoXY(mX, mY - 1);
	if (mX < colBoundary ) cout << " ";
	if (mX + 1 < colBoundary ) cout << " ";
	if (mX + 2 < colBoundary ) cout << " ";

	GotoXY(mX, mY);
	if (mX < colBoundary ) cout << " ";
	if (mX + 1 < colBoundary ) cout << " ";
	if (mX + 2 < colBoundary ) cout << " ";
}

bool CVEHICLE::checkPosition(int x, int boundary) {
	return x <= boundary && x >= 1;
}

CVEHICLE::CVEHICLE(int x, int y)
{
	mX = x;
	mY = y;
}


CVEHICLE::~CVEHICLE()
{
}

void CVEHICLE::Move(int lengthBoundary, int x) {
	mDelete();
}

void CVEHICLE::saveGame(ofstream& fo) {
	fo << mX << endl;
}


