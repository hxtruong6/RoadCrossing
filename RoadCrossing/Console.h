#pragma once
#include <windows.h>
#include <MMSystem.h>
#include <thread>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

__declspec(selectany) int columns, rows, colBoundary, rowBoundary;

void FixConsoleWindow();
void HideCursor(); //copy from internet
void GotoXY(int x, int y);
void GetSizeOfConsole();
void SetColor(int colorId);
char get_char_at_xy(int x, int y);
void animationLoading(int x, int y, int countDown = 25);

