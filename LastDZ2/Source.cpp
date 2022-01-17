#define _CRT_SECURE_NO_WARNINGS
#include"Cabinet.h"
#define Scrool 0
void fixWin() {
	SetConsoleTitleA("Test v1.0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#if Scrool == 1
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &info)) {
		COORD coord;
		coord.X = info.srWindow.Right - info.srWindow.Left + 1;
		coord.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
		SetConsoleScreenBufferSize(hConsoleOutput, coord);
	}
#endif
	HWND consoleWindow = GetConsoleWindow(); SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
int main() {
	fixWin();
	return start();
}