#pragma once
#include "Definition.h"
#include <fstream>


class CTRAFFICLIGHT
{
private:
	int m_state;
	int m_count;
public:
	CTRAFFICLIGHT(int count = 5, int state = GREEN) :m_count(count), m_state(state) {}
	~CTRAFFICLIGHT();

	void printTrafficLight(int x, int y);
	void switchState(int x, int y);
	int getState();
	void saveGame(std::ofstream&fo);
};

