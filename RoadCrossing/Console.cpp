#include "Console.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void HideCursor() //copy from internet
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GetSizeOfConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	colBoundary = columns - 30;
	rowBoundary = rows - 8;
	/*printf("columns: %d\n", columns);  //120
	printf("rows: %d\n", rows);*/		 //30
}

void SetColor(int colorId) {
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, colorId);
}

char get_char_at_xy(int x, int y) {
	CHAR_INFO ci;
	COORD xy = { 0, 0 };
	SMALL_RECT rect = { x, y, x, y };
	return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, { 1,1 }, xy, &rect) ? ci.Char.AsciiChar : '\0';
}

void animationLoading(int x, int y, int countDown) {
	GotoXY(x - 2, y + 6);
	SetColor(11); cout << "Loading Please Wait  ";
	Sleep(100);
	SetColor(14);
	std::cout << '-' << std::flush;
	for (int i = 0; i <= countDown; i++) {
		Sleep(20);
		std::cout << "\b\\" << std::flush;
		Sleep(20);
		std::cout << "\b|" << std::flush;
		Sleep(20);
		std::cout << "\b/" << std::flush;
		Sleep(20);
		std::cout << "\b-" << std::flush;
	}

	GotoXY(x - 2, y + 6);
	cout << "                                          ";

}
