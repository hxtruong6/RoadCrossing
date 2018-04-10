#include "CANIMAL.h"



CANIMAL::~CANIMAL()
{
}

void CANIMAL::Move(int lengthBoundary, int x) {
	mDelete();
}

void CANIMAL::saveGame(ofstream& fo) {
	fo << mX << endl;
}

void CANIMAL::mDelete() {
	GotoXY(mX, mY - 1);
	if (mX < colBoundary) cout << " ";
	if (mX + 1 < colBoundary) cout << " ";
	if (mX + 2 < colBoundary) cout << " ";

	GotoXY(mX, mY);
	if (mX < colBoundary) cout << " ";
	if (mX + 1 < colBoundary) cout << " ";
	if (mX + 2 < colBoundary) cout << " ";

}

bool CANIMAL::checkPosition(int x, int boundary) {
	return x <= boundary && x >= 1;
}