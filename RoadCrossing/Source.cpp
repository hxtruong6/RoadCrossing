#pragma once

#include "Console.h"
#include "CPEOPLE.h"
#include "CGAME.h"

CGAME* game;

enum MOVING {
	ILDE = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};
MOVING g_moving;

bool IS_RUNNING;


void PlayerInput(char keyPress)
{
	//if (GetKeyState(x) & 0x8000/*check if high-order bit is set (1 << 15)*/)
		//{
		//	// do stuff
		//}
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
		people->Left();
		break;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
		people->Right();
		break;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
		people->Up();
		break;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
		people->Down();
		break;
		}*/

	if (keyPress == 'A') {
		g_moving = LEFT;
	}
	else if (keyPress == 'D') {
		g_moving = RIGHT;
	}
	else if (keyPress == 'W') {
		g_moving = UP;
	}
	else if (keyPress == 'S') {
		g_moving = DOWN;
	}
	else g_moving = ILDE;
}

void SubThread() {
	while (IS_RUNNING) {
		if (!game->GetPeople()->IsDead()) {
			game->UpdatePosPeople(g_moving);
		}
		g_moving = ILDE;
		game->UpdatePosVehicle();
		game->UpdatePosAnimal();

		game->DrawGame();  //draw animal, vehicla move and people

		if (game->GetPeople()->IsImpact()) {
			PlaySound(TEXT("dieSound.wav"), NULL, SND_ASYNC);
			game->GetPeople()->animationDie();

			// Xử lý khi đụng xe hay thú
			SetColor(14); GotoXY(XINFO - 1, YINFO); cout << "OVER GAME!";
			SetColor(12); GotoXY(XINFO - 13, YINFO + 1); cout << "Press ";
			SetColor(15); cout << "Y";
			SetColor(12); cout << " to start new game";
			GotoXY(XINFO - 13, YINFO + 2); cout << "or press "; SetColor(15); cout << "B"; SetColor(12); cout << " back to menu";
			GotoXY(XINFO - 13, YINFO + 3); cout << "or press any key to quit.";

			IS_RUNNING = false;
		}
		if (game->GetPeople()->IsFinish()) {
			// Xử lý khi về đích
			game->SetNextLevel();
			game->StartGame();
		}
		Sleep(250);
	}
}

void newGame(bool &backToMenu) {
	animationLoading(XMENU, YMENU + 2, COUNTDOWN);
	bool restart;
	do {
		restart = false;
		bool isPause = false;

		//system("cls");
		if (!game) {
			game = new CGAME;
			game->StartGame();
		}
		IS_RUNNING = true;
		thread t(SubThread);
		while (true) {
			char keyPress = toupper(_getch());

			if (!game->GetPeople()->IsDead()) {
				if (keyPress == 27) {
					game->ExitGame(t, IS_RUNNING);
					delete game;  game = nullptr;
					return;
				}
				else if (keyPress == 'B') {
					backToMenu = true;
					PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
					game->ExitGame(t, IS_RUNNING);
					animationLoading(XINFO - 10, YINFO - 2, COUNTDOWN);

					delete game;  game = nullptr;
					return;
				}
				else if (!isPause && keyPress == 'P') {
					isPause = true;
					game->PauseGame((HANDLE)t.native_handle());
					SetColor(15); GotoXY(XPAUSE, YPAUSE); cout << "Enter any keyboard to continue game!";
				}
				else if (!isPause && keyPress == 'L') {
					game->PauseGame((HANDLE)t.native_handle()); 	Sleep(100);

					GotoXY(XPAUSE, YPAUSE); SetColor(11); cout << "Enter name file: ";
					string nameFile;
					SetColor(15); cin >> ws; getline(cin, nameFile);
					game->saveGame(nameFile);

					GotoXY(XPAUSE, YPAUSE); cout << "                                                            ";
					GotoXY(XPAUSE, YPAUSE); cout << "Enter any keyboard to continue game!";
					isPause = true;
				}
				else if (!isPause && keyPress == 'T') {
					game->PauseGame((HANDLE)t.native_handle()); 	Sleep(100);

					GotoXY(XPAUSE, YPAUSE); SetColor(11); cout << "Enter name file to load game: ";
					string nameFile;
					SetColor(15); cin >> ws; getline(cin, nameFile);
					bool check = false;
					game->loadGame(nameFile, check);

					GotoXY(XPAUSE, YPAUSE); cout << "                                                            ";
					GotoXY(XPAUSE, YPAUSE); cout << "Enter any keyboard to continue game!";
					isPause = true;
				}
				else {
					if (isPause) {
						isPause = false;
						GotoXY(XPAUSE, YPAUSE); cout << "                                    ";
						game->ResumeGame((HANDLE)t.native_handle());
					}
					PlayerInput(keyPress);
				}
			}
			else {
				game->ExitGame(t, IS_RUNNING);
				if (keyPress == 'Y') {
					restart = true;
					PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
					animationLoading(XINFO - 7, YINFO - 2, COUNTDOWN - 6);
					break;
				}
				else if (keyPress == 'B') {
					backToMenu = true;
					PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
					animationLoading(XINFO - 7, YINFO - 2, COUNTDOWN);
					delete game;  game = nullptr;
					return;
				}
				else {
					delete game;
					return;
				}
			}
		}
		delete game;  game = nullptr;
	} while (restart);
}

void menuGame(bool &backToMenu)
{
	system("cls");
	string str[11] = { "                    _________________________________________________",
						"            /|     |                                                 |",
						"            ||     |                                                 |",
						"       .----|-----,|                                                 |",
						"       ||  ||   ==||                                                 |",
						"  .-----'--'|   ==||                                                 |",
						"  |)-      ~|     ||_________________________________________________|",
						" | ___     |     |____/<_...==..._>\______________________________|   ",
						"[_/.-.\\ \"--\"-----------\\ .-.  .-./   |/            \\ .-.  .-. /  ",
						"  ( o )`===\"\"\"\"\"\"\"\"\"`   ( o )( o )    o            `( o )( o )`",
						"   '-'                   '-'  '-'                    '-'  '-'        " };

	SetColor(9);
	for (int i = 0; i < 11; ++i) {
		GotoXY(5, i);
		cout << str[i];

	}

	//print menu
	{
		SetColor(10); GotoXY(XMENU, YMENU); cout << "Game Road Crossing";
		SetColor(12);  GotoXY(XMENU + 1, YMENU + 1); cout << "1."; SetColor(15); cout << " New Game";
		SetColor(12); GotoXY(XMENU + 1, YMENU + 2); cout << "2."; SetColor(15); cout << " Load Game";
		SetColor(12); GotoXY(XMENU + 1, YMENU + 3); cout << "3."; SetColor(15); cout << " Setting";
		SetColor(12); GotoXY(XMENU + 1, YMENU + 4); cout << "4."; SetColor(15); cout << " Exit";
		SetColor(14); GotoXY(XMENU + 1, YMENU + 5); cout << "Enter(1/2/3/4): ";
	}

	while (true) {
		SetColor(10);  //cout << "\b";
		string choose;
		cin >> ws; getline(cin, choose);
		if (choose.size() == 1) {
			switch (choose[0]) {
			case '1':
			{
				newGame(backToMenu);
				return;
			}
			case '2':
			{
				SetColor(14);  GotoXY(XMENU + 1, YMENU + 6);
				string fileName;
				cout << "Enter name file game:  ";
				SetColor(15);  cin >> ws; getline(cin, fileName);
				if (game) {
					delete game; game = nullptr;
				}
				game = new CGAME;
				bool loadSuccessed = false;
				game->loadGame(fileName, loadSuccessed);
				if (loadSuccessed) {
					newGame(backToMenu);
				}
				else {
					backToMenu = true;
				}
				return;
			}
			case '3':
			{
				SetColor(11);  GotoXY(XMENU + 1, YMENU + 6);
				cout << "Enter level to play(1->7):  ";
				int level;
				SetColor(15);
				do {
					cout << "\b";
					cin >> level;
				} while (level < 1 || level > 7);
				if (game) {
					delete game; game = nullptr;
				}

				switch (level) {
				case 1: { level = LEVEL_1; break; }
				case 2: { level = LEVEL_2; break; }
				case 3: { level = LEVEL_3; break; }
				case 4: { level = LEVEL_4; break; }
				case 5: { level = LEVEL_5; break; }
				case 6: { level = LEVEL_6; break; }
				case 7: { level = LEVEL_7; break; }
				default:
					level = LEVEL_1;
				}
				game = new CGAME(level);
				game->StartGame();
				newGame(backToMenu);

				return;
			}
			case '4':
			{
				return;
			}
			default:
			{
				GotoXY(XMENU + 1, YMENU + 5);
				cout << "                                                                                                  ";
				SetColor(14);  GotoXY(XMENU + 1, YMENU + 5);
				cout << "Inavaible! Enter again(1/2/3/4): ";
			}
			}
		}
		else {
			GotoXY(XMENU + 1, YMENU + 5);
			cout << "                                                                                                  ";
			SetColor(14);  GotoXY(XMENU + 1, YMENU + 5);
			cout << "Inavaible! Enter again(1/2/3/4): ";
		}
	}

}

int main()
{
	FixConsoleWindow();
	GetSizeOfConsole();
	HideCursor();
	PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
	bool backToMenu;
	do {
		backToMenu = false;
		menuGame(backToMenu);
	} while (backToMenu);

	return EXIT_SUCCESS;
}