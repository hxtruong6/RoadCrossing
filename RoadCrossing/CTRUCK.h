#pragma once
#include "CVEHICLE.h"

class CTRUCK :public CVEHICLE {
	string mTruck[2];
public:
	CTRUCK(int x, int y) :CVEHICLE(x, y) {
		mTruck[1] = " " + string(1, 220) + string(1, 220);
		mTruck[0] = string(1, 220) + string(1, 219) + string(1, 219);
	}
	~CTRUCK();
	void DrawVehicle() override;

	void Move(int lengthBoundary, int x = 1);
	
};


