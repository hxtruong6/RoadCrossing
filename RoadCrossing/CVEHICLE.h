#pragma once
#include <string>
#include <iostream>
#include "Console.h"


using namespace std;
class CVEHICLE {
private: 
	void mDelete();
protected:
	int mX, mY; //   mX->mX+2, mY->mY+1
	bool checkPosition(int x, int boundary);
public:
	CVEHICLE(int x = 0, int y = 0);
	virtual ~CVEHICLE();
	virtual void Move(int lengthBoundary, int x = 1);
	virtual void DrawVehicle() = 0;
	void saveGame(ofstream& fo);
};

