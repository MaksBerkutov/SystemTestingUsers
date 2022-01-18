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
	HashSave Cur = GeTallHash(), file = GetFileLoadHash();
	if (strcmp(Cur.HashGroup, file.HashGroup) != 0) {
		system("cls");
		WordColor("Повержден файл сохранения групп\nФайл сохраненения групп будет очищен!\n", Black, Red); Test::Groups.ClearArr(); savegroup();
		system("pause"); system("cls");
	}
	if (strcmp(Cur.HashReport, file.HashReport) != 0) {
		system("cls");
		WordColor("Повержден файл сохранения репортов\nФайл сохраненения репортов будет очищен!\n", Black, Red); Report::rep.ClearArr(); savereport(); 
		system("pause"); system("cls");
	}
	if (strcmp(Cur.HashUser, file.HashUser) != 0) {
		system("cls");
		WordColor("Критичиская ошибка файл сохранения пользователей повреждён!\nПрограмма будет полностью очищенна!\n", Black, Red);
		system("pause"); system("cls"); ClearDataBaseAll();
		SaveHash(); saveall(); extraexit();
	}
	start();
	SaveHash();
	return 0;
	std::cout << getHash(dirsavename::dirSave + savename::NameSaveGroup) << std::endl;
	std::cout << getHash(dirsavename::dirSave + savename::NameSaveReport) << std::endl;
	std::cout << getHash(dirsavename::dirSave + savename::NameSaveUsers) << std::endl;
}
/*
8d0f2c24bc38e636fc42eb2dfc58b8b5
e702bfb5268530a5c71a18f965fb0889
39cf075bc0a86964377e390689cc7ece
*/
/*
128e701622313fdca8b04bde80d9d10f
cb74ac982eec9f722c7443989d23e256
6caf59a57d8d7237fbdf9a620d04d4da
*/