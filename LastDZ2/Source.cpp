#define _CRT_SECURE_NO_WARNINGS
#include"Cabinet.h"
#include"ChekerFile.h"
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
	HashSave Cur = GeTallHash(), file = GetFileLoadHash();
	if (strcmp(Cur.HashUser, file.HashUser) != 0) {
		system("cls");
		WordColor("Критическая ошибка файл сохранения пользователей повреждён!\nПрограмма будет полностью очищена!\n", Black, Red);
		system("pause"); system("cls"); ClearDataBaseAll();
		saveall(); SaveHash(); extraexit();
	}
	if (strcmp(Cur.HashGroup, file.HashGroup) != 0) {
		system("cls");
		WordColor("Поврежден файл сохранения групп\nФайл  сохранения  групп будет очищен!\n", Black, Red); Test::Groups.ClearArr(); savegroup();
		system("pause"); system("cls");
	}
	if (strcmp(Cur.HashReport, file.HashReport) != 0) {
		system("cls");
		WordColor("Поврежден файл сохранения репортов\nФайл сохранения  репортов будет очищен!\n", Black, Red); Report::rep.ClearArr(); savereport();
		system("pause"); system("cls");
	}
	start();
	SaveHash();
	return 0;
}