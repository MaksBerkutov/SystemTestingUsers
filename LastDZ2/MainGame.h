#pragma once
// c++17 | nlohman json libary
#include"Game.h"
void Start() {
	Games main;
	std::vector<std::string>mass = MapJson::GetNameMap();
	if (mass.size() == 0) {
		system("CLS"); WordColor("\t\tКарт нет!\n", Black, Red);
		system("pause"); system("CLS"); return;
	}
	for (int CurID = 0;;) {
		hidecursor();
		system("CLS");
		for (int i = 0; i < mass.size(); i++) {
			WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
			i == CurID ? WordColor(mass[i], Black, White) : WordColor(mass[i], Black, Blue);
			std::cout << std::endl;
		}
		switch (_getch()) {
		case Key_Up:
			if (CurID == 0) { CurID = mass.size()-1; }
			else { CurID--; }
			break;
		case Key_Down:
			if (CurID == mass.size() - 1) { CurID = 0; }
			else { CurID++; }
			break;
		case Key_Enter:
			main.Games::Games(mass[CurID]);
			system("pause");
			system("CLS");
			break;
		case Key_q:
			showursor();
			system("CLS");
			return;
			break;

		}
	}
}
void GameMain() {
	std::string pn[3] = { "Конструктор карт","Страт игры","Выход" };
	for (;;) {
		switch (MenuMain(pn, 3)) {
		case 0:
			CreateMap();
			break;
		case 1:
			Start();
			break;
		case 2:
			return;
		}
	}
}

