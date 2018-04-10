#pragma once
#include "CANIMAL.h"

class CDINAUSOR:public CANIMAL
{
	string mDinausor[2];
public:
	CDINAUSOR(int x, int y) :CANIMAL(x, y) {
		mDinausor[0] = string(1, 220) + string(1, 219) + string(1,223);
		mDinausor[1] = "  " + string(1, 220);
	}
	
	~CDINAUSOR();

	void DrawAnimal() override;
	void Move(int lengthBoundary, int x=1);
};

