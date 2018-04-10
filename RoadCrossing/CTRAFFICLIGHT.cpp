#include "CTRAFFICLIGHT.h"
#include "Console.h"
#include <ctime>


CTRAFFICLIGHT::~CTRAFFICLIGHT()
{
}

void CTRAFFICLIGHT::printTrafficLight(int x, int y) {
	switch (m_state) {
	case RED: {
		SetColor(12);
		GotoXY(x, y + 1); cout << char(219);
		break;
	}
	case YELLOW: {
		SetColor(14);
		GotoXY(x, y); cout << char(219);
		break;
	}
	case GREEN: {
		SetColor(10);
		GotoXY(x, y - 1); cout << char(219);
		break;
	}
	}
	//GotoXY(x, y); cout << char(219);
}

void CTRAFFICLIGHT::switchState(int x, int y) {
	m_count--;
	if (m_count == 0) {
		switch (m_state) {
		case RED: {
			GotoXY(x, y + 1);
			m_state = GREEN;
			m_count = rand() % (COUNTDOWNCHANGELIGHT + 4);
			break;
		}
		case YELLOW: {
			GotoXY(x, y);
			m_state = RED;
			m_count = rand() % (COUNTDOWNCHANGELIGHT + 10);
			break;
		}
		case GREEN: {
			GotoXY(x, y - 1);
			m_state = YELLOW;
			m_count = rand() % (COUNTDOWNCHANGELIGHT + 10);
			break;
		}
		}
		//GotoXY(x, y); 
		SetColor(8); cout << char(219);
		srand(time(nullptr));

	}
}

int CTRAFFICLIGHT::getState() {
	return m_state;
}

void CTRAFFICLIGHT::saveGame(std::ofstream& fo) {
	fo << m_state << " " << m_count << endl;
}
