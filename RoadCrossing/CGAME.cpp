#include "CGAME.h"
#include <ctime>
#include "CTRUCK.h"
#include "CCAR.h"
#include "CBIRD.h"
#include "CDINAUSOR.h"


void CGAME::SpawnObject() {
	//determind block consist of object(3) + space(?)
	m_block = ceil(((float)colBoundary - 2) / (float)m_level);

	m_cvehicles.clear();
	m_canimals.clear();

	for (int i = 0; i < m_level; ++i) {
		m_cvehicles.push_back(new CTRUCK(m_block*i + 1, LANE_4));
		m_cvehicles.push_back(new CCAR(m_block*i + 1, LANE_3));
		m_canimals.push_back(new CBIRD(m_block*i + 1, LANE_2));
		m_canimals.push_back(new CDINAUSOR(m_block*i + 1, LANE_1));
	}


	//for (int i = 0; i < m_level; ++i) {
	//	m_canimals.push_back(new CBIRD(m_block*i + 1, LANE_2));
	//	m_canimals.push_back(new CDINAUSOR(m_block*i + 1, LANE_1));
	//}
}

void CGAME::printLevel() {
	GotoXY(XINFO, YINFO);
	SetColor(10);
	switch (m_level) {
	case LEVEL_1: {
		cout << "LEVEL 1";
		break;
	}
	case LEVEL_2: {
		cout << "LEVEL 2";
		break;
	}
	case LEVEL_3: {
		cout << "LEVEL 3";
		break;
	}
	case LEVEL_4: {
		cout << "LEVEL 4";
		break;
	}
	case LEVEL_5: {
		cout << "LEVEL 5";
		break;
	}
	case LEVEL_6: {
		cout << "LEVEL 6";
		break;
	}
	case LEVEL_7: {
		cout << "MAX LEVEL";
		SetColor(11); GotoXY(100, 9); cout << "You are the best!!!";
		break;
	}
	default: break;
	}
}

void CGAME::printHelp() {
	GotoXY(XINFO - 8, YINFO - 7);
	SetColor(12); cout << "Help";

	GotoXY(XINFO - 12, YINFO - 6);
	SetColor(11); cout << "W";
	SetColor(8);  cout << "/";
	SetColor(11); cout << "S";
	SetColor(8);  cout << "/";
	SetColor(11); cout << "A";
	SetColor(8);  cout << "/";
	SetColor(11); cout << "D";
	SetColor(8);  cout << ": up/down/left/right";

	GotoXY(XINFO - 12, YINFO - 5);
	SetColor(8); cout << "Press ";
	SetColor(11); cout << "P";
	SetColor(8);  cout << " to pause game";

	GotoXY(XINFO - 12, YINFO - 4);
	SetColor(8); cout << "Press ";
	SetColor(11); cout << "T";
	SetColor(8);  cout << " to load game";
	
	GotoXY(XINFO - 12, YINFO - 3);
	SetColor(8); cout << "Press ";
	SetColor(11); cout << "L";
	SetColor(8);  cout << " to save game";

	GotoXY(XINFO - 12, YINFO - 2); 
	SetColor(8); cout << "Press ";
	SetColor(11); cout << "B";
	SetColor(8);  cout << " to back game";

	GotoXY(XINFO - 12, YINFO - 1); 
	SetColor(8); cout << "Press ";
	SetColor(11); cout << "ESC";
	SetColor(8);  cout << " to quit game";
}


CGAME::CGAME(int level)
{
	this->m_level = level;
	m_trafficlight_car = new CTRAFFICLIGHT(COUNTDOWNCHANGELIGHT, GREEN);
	m_trafficlight_truck = new CTRAFFICLIGHT(COUNTDOWNCHANGELIGHT, GREEN);
}

void DrawBoundary() {
	SetColor(8);
	for (int i = 0; i < colBoundary; i++) {
		char t = 219;
		GotoXY(i, 0); cout << char(219);
		GotoXY(i, rowBoundary); cout << char(219);
	}
	for (int i = 0; i <= rowBoundary; i++) {
		GotoXY(0, i); cout << char(219);
		GotoXY(colBoundary, i); cout << char(219);
	}

	for (int i = 1; i < colBoundary; ++i) {
		SetColor(10);
		GotoXY(i, 3); cout << char(240);

		SetColor(11);
		GotoXY(i, 7); cout << char(174);
		GotoXY(i, 11); cout << char(175);
		GotoXY(i, 15); cout << char(174);

		SetColor(10);
		GotoXY(i, 19); cout << char(240);
	}
	SetColor(7);
}

void CGAME::DrawGame()
{
	m_people->DrawPeople();
	m_trafficlight_car->printTrafficLight(colBoundary, LANE_3);
	m_trafficlight_truck->printTrafficLight(0, LANE_4);
	for (CVEHICLE* cvehicle : m_cvehicles) {
		cvehicle->DrawVehicle();
	}
	for (CANIMAL* canimal : m_canimals) {
		canimal->DrawAnimal();
	}
}

CGAME::~CGAME()
{
	delete m_people;
	delete m_trafficlight_car;
	delete m_trafficlight_truck;
}

CPEOPLE* CGAME::GetPeople()
{
	return m_people;
}

void CGAME::ResetGame() {
	m_level = LEVEL_1;
	this->StartGame();
}

void CGAME::ExitGame(thread& t, bool& IS_RUNNING) {
	IS_RUNNING = false;
	if (t.joinable())
		t.join();
}


void CGAME::StartGame()
{
	system("cls");
	DrawBoundary();
	SpawnObject();
	if (m_people)
		delete m_people;
	this->m_people = new CPEOPLE();
	printLevel();
	printHelp();
}

void CGAME::loadGame(const string& fileName, bool &succeeded) {
	ifstream fi;
	fi.open(fileName);
	if (!fi.is_open()) {
		succeeded = false;
		GotoXY(XPAUSE + 5, YPAUSE + 1);
		SetColor(15); cout << "Cant't load game! Error";
		Sleep(2000);
		GotoXY(XPAUSE + 5, YPAUSE + 1); cout << "                                       ";
		return;
	}

	int mX, mY, mState, mType, length;

	//read people
	fi >> mX >> mY >> mState;
	if (m_people)
		delete m_people;
	m_people = new CPEOPLE(mX, mY, mState);

	//read vehicles
	fi >> length;
	m_cvehicles.clear();
	for (int i = 0; i < length; ++i) {
		fi >> mType >> mX;
		if (mType == 0)
			m_cvehicles.push_back(new CTRUCK(mX, LANE_4));
		else
			m_cvehicles.push_back(new CCAR(mX, LANE_3));
	}

	//read animals
	fi >> length;
	m_canimals.clear();
	for (int i = 0; i < length; ++i) {
		fi >> mType >> mX;
		if (mType == 0)
			m_canimals.push_back(new CBIRD(mX, LANE_2));
		else
			m_canimals.push_back(new CDINAUSOR(mX, LANE_1));
	}

	//read traffic light
	int mCount;
	fi >> mState >> mCount;
	delete m_trafficlight_truck;
	m_trafficlight_truck = new CTRAFFICLIGHT(mCount, mState);

	fi >> mState >> mCount;
	delete m_trafficlight_car;
	m_trafficlight_car = new CTRAFFICLIGHT(mCount, mState);

	//read block read level
	fi >> m_block >> m_level;

	GotoXY(XPAUSE + 5, YPAUSE + 1);
	SetColor(10); cout << "Load game successfull!";
	Sleep(300);
	GotoXY(XPAUSE + 5, YPAUSE + 1); cout << "                          ";
	fi.close();

	//print all things
	{
		system("cls");
		DrawBoundary();
		DrawGame();
		printHelp();
		printLevel();
	}

	succeeded = true;
}

void CGAME::saveGame(const string& fileName) {
	/*
	 * save game
	 * People: mX mY mState
	 * Number of vehicle: n
	 * (0/1: truck/car): mX    //mY == LANE_*
	 * ...
	 * Number of animal: m
	 * (0/1: bird/dinausor): mX mY
	 * ...
	 * Traffic light truck: mState mCount
	 * Traffic light car: mState mCount
	 * Block Level of game: m_block m_level
	 */

	ofstream fo;
	fo.open(fileName, ofstream::trunc);
	if (!fo.is_open()) {
		GotoXY(XPAUSE + 5, YPAUSE + 1);
		SetColor(15); cout << "Cant't save game! Error";
		Sleep(2000);
		GotoXY(XPAUSE + 5, YPAUSE + 1); cout << "                                       ";
		return;
	}
	m_people->saveGame(fo);

	//number of vehicle
	fo << m_cvehicles.size() << endl;
	for (CVEHICLE* vehicle : m_cvehicles) {
		if (dynamic_cast<CTRUCK*>(vehicle))
			fo << 0 << " ";
		else
			fo << 1 << " ";
		vehicle->saveGame(fo);
	}

	//number of animal
	fo << m_canimals.size() << endl;
	for (CANIMAL* animal : m_canimals) {
		if (dynamic_cast<CBIRD*>(animal))
			fo << 0 << " ";
		else
			fo << 1 << " ";
		animal->saveGame(fo);
	}

	//write state of traffic light
	m_trafficlight_truck->saveGame(fo);
	m_trafficlight_car->saveGame(fo);

	//write block and level of game
	fo << m_block << " " << m_level;

	//check if file is written successful
	if (fo) {
		GotoXY(XPAUSE + 5, YPAUSE + 1);
		SetColor(15); cout << "Save successfull!";
	}
	else {
		GotoXY(XPAUSE + 5, YPAUSE + 1);
		SetColor(15); cout << "Save ";
		SetColor(12); cout << "not";
		SetColor(15); cout << " successfull!";
	}
	Sleep(500);
	GotoXY(XPAUSE + 5, YPAUSE + 1); cout << "                                       ";
	fo.close();
}

void CGAME::PauseGame(HANDLE handle) {
	SuspendThread(handle);
}

void CGAME::ResumeGame(HANDLE handle) {
	ResumeThread(handle);
}

void CGAME::UpdatePosPeople(MOVING moving)
{
	switch (moving) {
	case 1:
	{
		m_people->Up();
		break;
	}
	case 2:
	{
		m_people->Down();
		break;
	}
	case 3:
	{
		m_people->Left();
		break;
	}
	case 4:
	{
		m_people->Right();
		break;
	}
	}
}

void CGAME::UpdatePosVehicle()
{
	m_trafficlight_truck->switchState(0, LANE_4);
	m_trafficlight_car->switchState(colBoundary, LANE_3);
	for (CVEHICLE* vehicle : m_cvehicles) {
		if (dynamic_cast<CTRUCK*>(vehicle))
			vehicle->Move(m_block*m_level, m_trafficlight_truck->getState());
		else
			vehicle->Move(m_block*m_level, m_trafficlight_car->getState());
	}
}

void CGAME::UpdatePosAnimal() {
	for (CANIMAL* animal : m_canimals) {
		animal->Move(m_block*m_level);
	}
}

void CGAME::SetNextLevel() {
	switch (m_level) {
	case LEVEL_1: {
		m_level = LEVEL_2;
		break;
	}
	case LEVEL_2: {
		m_level = LEVEL_3;
		break;
	}
	case LEVEL_3: {
		m_level = LEVEL_4;
		break;
	}
	case LEVEL_4: {
		m_level = LEVEL_5;
		break;
	}
	case LEVEL_5: {
		m_level = LEVEL_6;
		break;
	}
	case LEVEL_6: {
		m_level = LEVEL_7;
		break;
	}
	default: break;
	}

}



