#pragma once
#include "CVEHICLE.h"
class CCAR :public CVEHICLE
{
	string mCar[2];
public:
	CCAR(int x, int y) :CVEHICLE(x, y) {
		mCar[0] = string(1, 219) + string(1, 219) + string(1, 219);
		mCar[1] = " " + string(1, 220) + " ";
	}
	~CCAR();
	void DrawVehicle() override;

	void Move(int lengthBoundary, int x = 1);
	
};

