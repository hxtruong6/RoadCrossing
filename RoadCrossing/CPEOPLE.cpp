#include "CPEOPLE.h"
#include "Definition.h"


void CPEOPLE::mDelete()
{
	if (mY <= 1) return;
	GotoXY(this->mX, this->mY);
	cout << " ";
	GotoXY(this->mX, this->mY - 1);
	cout << " ";
}

void CPEOPLE::DrawPeople()
{
	if (mY <= 1) return;
	GotoXY(this->mX, this->mY);
	SetColor(14); cout << this->mPeople[0];
	GotoXY(this->mX, this->mY - 1);
	SetColor(15); cout << this->mPeople[1];
}

void CPEOPLE::animationDie() {
	for (int i = 0; i < COUNTDOWN - 8; ++i) {
		GotoXY(mX, mY);	SetColor(12); cout << char(207);

		GotoXY(mX - 1, mY); SetColor(4); cout << char(177);
		GotoXY(mX + 1, mY); SetColor(4); cout << char(177);
		GotoXY(mX, mY - 1); SetColor(4); cout << char(177);
		GotoXY(mX, mY + 1); SetColor(4); cout << char(177);

		GotoXY(mX - 1, mY - 1); SetColor(5); cout << char(176);
		GotoXY(mX - 1, mY + 1); SetColor(5); cout << char(176);
		GotoXY(mX + 1, mY - 1); SetColor(5); cout << char(176);
		GotoXY(mX + 1, mY + 1); SetColor(5); cout << char(176);

		Sleep(80);
		GotoXY(mX, mY);	SetColor(12); cout << char(206);

		GotoXY(mX - 1, mY); SetColor(4); cout << char(178);
		GotoXY(mX + 1, mY); SetColor(4); cout << char(178);
		GotoXY(mX, mY - 1); SetColor(4); cout << char(178);
		GotoXY(mX, mY + 1); SetColor(4); cout << char(178);

		GotoXY(mX - 1, mY - 1); SetColor(5); cout << char(177);
		GotoXY(mX - 1, mY + 1); SetColor(5); cout << char(177);
		GotoXY(mX + 1, mY - 1); SetColor(5); cout << char(177);
		GotoXY(mX + 1, mY + 1); SetColor(5); cout << char(177);

		Sleep(80);
	}

}

void CPEOPLE::saveGame(ofstream& fo) {
	fo << mX << " " << mY << " " << mState << endl;
}

CPEOPLE::CPEOPLE(int x, int y, int state)
{
	mPeople[0] = string(1, 185);
	mPeople[1] = string(1, 148);
	this->mX = x;
	this->mY = y;
	this->mState = state;
}


CPEOPLE::~CPEOPLE()
{
}

void CPEOPLE::Up()
{
	/*if (this->mY == 0)
		return;*/
	this->mDelete();

	if (mY == 5) mY -= 3;
	else this->mY -= 4;

}

void CPEOPLE::Left()
{
	if (this->mX == 1)
		return;
	this->mDelete();

	this->mX--;

}

void CPEOPLE::Right()
{
	if (this->mX == colBoundary - 1)
		return;
	this->mDelete();
	this->mX++;
}

void CPEOPLE::Down()
{
	if (this->mY == rowBoundary - 1)
		return;
	this->mDelete();
	if (mY == 2) mY += 3;
	else this->mY += 4;
}

bool CPEOPLE::IsImpact() {
	/*char t = get_char_at_xy(mX, mY);
	char t1 = get_char_at_xy(mX, mY - 1);
	GotoXY(110, 2); cout << t << "  " << t1;*/

	if ((mY > 1) && (get_char_at_xy(mX, mY) != mPeople[0][0] || get_char_at_xy(mX, mY - 1) != mPeople[1][0])) {
		mState = false;
		return true;
	}
	return false;

}

bool CPEOPLE::IsFinish()
{
	return this->mY <= 1;
}

bool CPEOPLE::IsDead()
{
	return !this->mState;
}