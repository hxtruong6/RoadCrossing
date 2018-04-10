#pragma once

#include  "thread"
#include "Console.h"
#include "Definition.h"
#include "CVEHICLE.h"
#include "CPEOPLE.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <map>
#include "CANIMAL.h"
#include "CTRAFFICLIGHT.h"
#include <fstream>



using namespace std;
class CGAME {
private:
	CPEOPLE *m_people;
	vector<CVEHICLE*> m_cvehicles;
	vector<CANIMAL*> m_canimals;
	CTRAFFICLIGHT *m_trafficlight_car, *m_trafficlight_truck;

	void SpawnObject();
	void printLevel();
	void printHelp();
	int m_block;
	int m_level;
public:

	CGAME(int level = LEVEL_1);  //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void DrawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE* GetPeople();//Lấy thông tin người

	void ResetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void ExitGame(thread &, bool&); // Thực hiện thoát Thread

	void StartGame(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(const string& fileName, bool &succeeded ); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(const string& fileName); // Thực hiện lưu lại dữ liệu trò chơi
	void PauseGame(HANDLE); // Tạm dừng Thread
	void ResumeGame(HANDLE); //Quay lai Thread
	void UpdatePosPeople(enum MOVING); //Thực hiện điều khiển di chuyển của CPEOPLE
	void UpdatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void UpdatePosAnimal();//Thực hiện cho CDINAUSOR & CBIRD di chuyển

	void SetNextLevel();
	
	
};


