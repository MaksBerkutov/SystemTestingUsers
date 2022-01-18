#pragma once
#include"ArrayClass.h"
#include"md5.h"
#include"GetValue.h"
#include"Menuh.h"
#include"Date.h"
#include"SaveLoad.h"
#include<string>
#include<iostream>
namespace Users {
	static int UserID = -1;
	struct User {
		std::string Country;
		std::string MobilePhone;
		std::string NameUsers;
		char login[33], passw[33];
		bool Admins;
		time_t LastConect;
	};
	static Array::ArrayClass<User>usr;
	int loginSystem(std::string pass, std::string login) {//Функция аунтефикации
		for (int i = 0; i < usr.getSize(); i++) {
			if (strcmp(usr[i].login, login.c_str()) == 0) {
				if (strcmp(usr[i].passw, pass.c_str()) == 0) {
					return i;
				}
				else return -1;
			}
		}
		return -1;
	}
	Array::ArrayClass<int> getInputUsersGUI() {
		Array::ArrayClass<int> res;
		bool* ids = new bool[usr.getSize()]{ false };
		for (int CurID = 0;;) {
			system("CLS");
			hidecursor();
			for (size_t i = 0; i < usr.getSize(); i++) {
				hidecursor();
				WordColor(("\t" + std::to_string(i) + ") "), Black, Blue, Black, LightGreen);
				if (i == CurID) {
					if (ids[i] != false) {
						WordColor(("[+]: " + usr[i].NameUsers + "\n"), Black, White, Black, LightGreen);
					}
					else {
						WordColor(("[ ]: " + usr[i].NameUsers+"\n"), Black, White, Black, LightGreen);
					}
				}
				else {
					if (ids[i] != false) {
						WordColor(("[+]: " + usr[i].NameUsers + "\n"), Black, Red, Black, LightGreen);
					}
					else {
						WordColor(("[ ]: " + usr[i].NameUsers + "\n"), Black, Red, Black, LightGreen);
					}
				}
			}
			switch (_getch()) {
			case Key_Up:
				if (CurID == 0)CurID = usr.getBackIndex();
				else CurID--;
				break;
			case Key_Down:
				if (CurID == usr.getBackIndex())CurID = 0;
				else CurID++;
				break;
			case Key_Enter:
				ids[CurID] = !ids[CurID];
				break;
			case Key_q:
				for (size_t i = 0; i < usr.getSize(); i++) {
					if (ids[i] != false) { res.addItem(i); }
				}
				showursor();
				return res;
				break;
			}
		}
	}
	void PrintIDUsersGUI() {
		for (size_t i = 0; i < usr.getSize(); i++) {
			WordColor(("\t" + std::to_string(i) + ") "), Black, Blue, Black, LightGreen); std::cout << usr[i].NameUsers << std::endl;
		}
	}
	void CreateUser() {
		usr.addItem();
		WordColor("Имя пользователя > ", Black, LightRed, Black, LightBlue); getline(std::cin, usr[usr.getBackIndex()].NameUsers);
		WordColor("Мобильный телефон > ", Black, LightRed, Black, LightBlue); getline(std::cin, usr[usr.getBackIndex()].MobilePhone);
		WordColor("Адресс > ", Black, LightRed, Black, LightBlue); getline(std::cin, usr[usr.getBackIndex()].Country);
		bool flg = false;
		for (std::string tmp;;) {
			flg = false;
			WordColor("Логин > ", Black, LightRed, Black, LightBlue); getline(std::cin, tmp); strcpy_s(usr[usr.getBackIndex()].login, 33, md5(tmp).c_str());
			for (int i = 0; i < usr.getSize() - 1; i++) {
				if (strcmp(usr[usr.getBackIndex()].login, usr[i].login) == 0) { flg = !flg; break; }
			}
			if (flg != false) { system("CLS"); WordColor("Ошибка такой логин уже есть!\n", Black, Red, Black, LightGray); system("pause"); system("CLS"); }
			else { WordColor("Пароль > ", Black, LightRed, Black, LightBlue); getline(std::cin, tmp); strcpy_s(usr[usr.getBackIndex()].passw, 33, md5(tmp).c_str()); break; };
		}
		usr[usr.getBackIndex()].Admins = false;
	}
	void getAdminsRulesID(int ID) {
		if (ID >= 0 && ID > usr.getSize() || usr[ID].Admins == false) {
			usr[ID].Admins = true;
		}
		else {
			system("CLS");
			WordColor("\t\tПользователь уже администратор или не верный ID!\n", Black, Red);
			system("pause");
			system("CLS");
		}
	}
	std::string getNameLogin(char log[33]) {
		for (int i = 0; i < usr.getSize(); i++) {
			if (strcmp(usr[i].login, log) == 0) { return static_cast<std::string>(usr[i].NameUsers); }
		}
		return"пользователь удалён!";
	}
	int Auntification(int loading = 3) {
		system("CLS");
		const float ver_log = 2.4;
		std::cout << std::setw(8) << std::setfill('\n') << "" << std::setfill(' ') << std::endl;
		WordColor("\t\t\t\t\t\tСистема логирования v", Black, LightGreen, Black, Red);
		std::cout << ver_log << std::endl;
		UserID = loginSystem(md5(GetVal::getValString("\t\t\t\t\t\tВведите пароль > ")), md5(GetVal::getValString("\t\t\t\t\t\tВведите логин > ")));
		if (UserID < 0) {
			system("CLS");
			WordColor(("\n\n\n\n\t\t\t\tНе верный пароль или логин попробуйте ещё раз у вас осталось " + std::to_string(loading) + " попыток\n"), Black, Blue);
			system("pause");
			system("CLS");
			if (loading == 0) { return 3; }//No authorizated
			else return Auntification(--loading);
		}
		else {
			usr[UserID].LastConect = time(NULL);
			system("CLS");
			return 0;
		}
	}
	void printUsrID(int ID) {
		system("CLS");
		WordColor("Имя: ", Black, LightRed, Black, LightBlue); std::cout << usr[ID].NameUsers << std::endl;
		WordColor("Мобильный телефон: ", Black, LightRed, Black, LightBlue); std::cout << usr[ID].MobilePhone << std::endl;
		WordColor("Адреc: ", Black, LightRed, Black, LightBlue); std::cout << usr[ID].Country << std::endl;
		WordColor("Последний вход: ", Black, LightRed, Black, LightBlue);
		if (usr[ID].LastConect < 1000) { std::cout << "Не входил" << std::endl;; }
		else {
			std::cout << Dates::Date::getStringDate(usr[ID].LastConect) << std::endl;
		}
	}
	void PrintUser() {
		Array::ArrayClass<int> inp = getInputUsersGUI();
		for (size_t i = 0; i < inp.getSize(); i++) {
			printUsrID(inp[i]);
			system("pause");
			system("cls");
		}
	}
	//std::string getValString(std::string str) {
	//	WordColor(str, Black, LightGreen, Black, Red); std::string num; std::getline(std::cin, num);
	//	return num;
	//}
	void editUser(int ID) {
		std::string tmp; bool check = false;
		std::string punkt[6] = { "Новое имя","Новый адресс","Новый мобильный телефон","Новый логин","Новый пароль","Выход" };
		for (;;) {
			switch(MenuMain(punkt, 6)) {
			case 0:
				WordColor("Введите имя > ", Black, LightGreen, Black, Red); std::getline(std::cin, usr[ID].NameUsers);
				break;
			case 1:
				WordColor("Введите адресс > ", Black, LightGreen, Black, Red); std::getline(std::cin, usr[ID].Country);
				break;
			case 2:
				WordColor("Введите адресс > ", Black, LightGreen, Black, Red); std::getline(std::cin, usr[ID].MobilePhone);
				break;
			case 3:
				check = false;
				tmp = GetVal::getValString("Введите логин > ");
				for (int i = 0; i < usr.getSize(); i++) {
					if (strcmp(md5(tmp).c_str(), usr[i].login) == 0) {
						system("CLS"); WordColor("Ошибка такой логин уже есть!\n", Black, Red); check = true; system("pause"); system("CLS"); break;
					}
				}
				if (check != true)std::strcpy(usr[ID].login, md5(tmp).c_str());
				break;
			case 4:
				std::strcpy(usr[ID].passw, md5(GetVal::getValString("Введите пароль > ")).c_str());
				break;
			case 5:
				Save::Save(usr.getArr(), usr.getSize(), savename::NameSaveUsers);
				if (ID == UserID) {  exit(-1); }
				return;
			}
		}
	}
	int getUserGUI() {
		for (int CurID = 0;;) {
			hidecursor();
			system("CLS");
			for (int i = 0; i < usr.getSize(); i++) {
				WordColor(("\t" + std::to_string(i) + ") "), Black, Blue);
				CurID == i ? WordColor(usr[i].NameUsers, Black, White) : WordColor(usr[i].NameUsers, Black, Red);
				std::cout << std::endl;
			}
			switch (_getch()) {
			case Key_Up:
				if (CurID == 0)CurID = usr.getBackIndex();
				else CurID--;
				break;
			case Key_Down:
				if (CurID == usr.getBackIndex())CurID = 0;
				else CurID++;
				break;
			case Key_Enter:
				showursor();
				return CurID;
				break;
			}
		}
	}

	int Save() {
		return Save::Save(usr.getArr(), usr.getSize(), savename::NameSaveUsers);
	}
	int Load() {
		return Load::Load(usr.getArrAdress(), usr.getSizeAdress(), savename::NameSaveUsers);
	}

}
