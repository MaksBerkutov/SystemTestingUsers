#pragma once
#include"Test.h"
#include"CMD.h"
#include"Report.h"
#include<algorithm>
#include"Hash.h"
struct HashSave {
	char HashGroup[33];
	char HashUser[33];
	char HashReport[33];
};
HashSave GeTallHash() {
	HashSave hash;
	strcpy_s(hash.HashGroup, 33, getHash(dirsavename::dirSave + savename::NameSaveGroup).c_str());
	strcpy_s(hash.HashUser, 33, getHash(dirsavename::dirSave + savename::NameSaveUsers).c_str());
	strcpy_s(hash.HashReport, 33, getHash(dirsavename::dirSave + savename::NameSaveReport).c_str());
	return hash;
}
void SaveHash() {
	std::fstream File; File.open(savename::NameSaveHash, std::ios::out | std::ios::trunc);
	File << getHash(dirsavename::dirSave + savename::NameSaveGroup) << std::endl;
	File << getHash(dirsavename::dirSave + savename::NameSaveUsers) << std::endl;
	File << getHash(dirsavename::dirSave + savename::NameSaveReport) << std::endl;
	File.close();
}
HashSave GetFileLoadHash() {
	HashSave hash;
	std::fstream File; File.open(savename::NameSaveHash, std::ios::in);
	File >> hash.HashGroup;
	File >> hash.HashUser;
	File >> hash.HashReport;
	return hash;
}
int start();
//==============
void saveusers() { Users::Save(); }
void savereport() { Save::Save(Report::rep.getArr(), Report::rep.getSize(),savename::NameSaveReport); }
void savegroup() { Test::Save(Test::Groups); }
void saveall() { saveusers(); savegroup(); savereport(); }
void loadusers() { Users::Load(); }
void loadreport() { Load::Load(Report::rep.getArrAdress(), Report::rep.getSizeAdress(), savename::NameSaveReport); }
void loadgroup() { Test::Load(Test::Groups); }
void loadall() { loadusers(); loadgroup(); loadreport(); }
void ClearDataBaseAll() {
	Users::usr.ClearArr();
	Test::Groups.ClearArr();
	Report::rep.ClearArr();
}
void DeleteDataBase() {
	system("CLS");
	ClearDataBaseAll();
	saveall();
	WordColor("\t\tБазы даных очищены!\n", Black, Red); system("pause"); system("CLS"); exit(-11);
}
//================
void AdmGetAnswerRep(Report::Info& obj) {
	strcpy_s(obj.IDOut,33, Users::usr[Users::UserID].login);
	WordColor("Вопрос: ", Black, Red, Black, Green); std::cout << obj.MsgIn << std::endl;
	WordColor("Введите ваш ответ > ", Black, Red, Black, Green); std::cin.getline(obj.MsgOut,256);
}
void PrintRep(Report::Info& obj) {
	WordColor("Имя подавщего заявку: ", Black, Red, Black, Green); std::cout << Users::getNameLogin(obj.IDIn) << std::endl;
	WordColor("Имя: ", Black, Red, Black, Green); std::cout << obj.Name << std::endl;
	WordColor("Вопрос: ", Black, Red, Black, Green); std::cout << obj.MsgIn << std::endl;
	if (strlen(obj.IDOut) < 2) {
		WordColor("Имя администратора: ", Black, Red, Black, Red); std::cout << "Репорт не проверен!\n" << std::endl;
		WordColor("Ответ: ", Black, Red); std::cout << "Ответ не был дан!\n" << std::endl;
	}
	else {
		WordColor("Имя администратора: ", Black, Red, Black, Red); std::cout << Users::getNameLogin(obj.IDOut) << std::endl;
		WordColor("Ответ: ", Black, Red, Black, Green); std::cout << obj.MsgOut << std::endl;
	}
	system("pause");
}
void RepMenu() {
	if (Users::usr[Users::UserID].Admins != false) {
		
		for (int curent = 0;;) {
			hidecursor();
			for (int i = 0; i < Report::rep.getSize(); i++) {
				i == curent ? WordColor("\t|  ", Black, Blue, Black, White) : WordColor("\t| ", Black, Blue, Black, Red);
				std::cout << Report::rep[i].Name;
				WordColor(" | ", Black, Blue, Black, White);
				if (strlen(Report::rep[i].IDOut) < 2) { WordColor("Не отвеченно\n", Black, Blue, Black, Red); }
				else { WordColor("Есть ответ\n", Black, Blue, Black, Green); }
			}
			switch (_getch()) {
			case Key_Up:
				if (curent == 0) { curent = Report::rep.getBackIndex(); }
				else { curent--; }
				break;
			case Key_Down:
				if (curent == Report::rep.getBackIndex()) { curent = 0; }
				else { curent++; }
				break;
			case Key_Enter:
				showursor();
				system("CLS");
				if (strlen(Report::rep[curent].IDOut) < 2) { AdmGetAnswerRep(Report::rep[curent]);}
				else { PrintRep(Report::rep[curent]); }
				//return curent;
			case Key_q:
				showursor();
				system("CLS");
				return;
				//return curent;
			}
			system("CLS");
		}
	}
	else {
		Array::ArrayClass<int>idsrep = Report::getRepsLogin(Users::usr[Users::UserID].login);
		if (idsrep.getSize() < 1) { WordColor("\t\tУ вас нет репортов!\n", Black, Red); system("pause"); system("CLS"); return; }
		for (int curent = 0;;) {
			hidecursor();
			for (int i = 0; i < idsrep.getSize(); i++) {
				i == curent? WordColor("\t|  ", Black, Blue, Black, White): WordColor("\t| ", Black, Blue, Black, Red);
				std::cout << Report::rep[idsrep[i]].Name;
				WordColor(" | ", Black, Blue, Black, White);
				if (strlen(Report::rep[idsrep[i]].IDOut)<2) { WordColor("Не отвеченно\n", Black, Blue, Black, Red);  }
				else { WordColor("Есть ответ\n", Black, Blue, Black, Green); }
			}
			switch (_getch()) {
			case Key_Up:
				if (curent == 0) { curent = idsrep.getBackIndex(); }
				else { curent--; }
				break;
			case Key_Down:
				if (curent == idsrep.getBackIndex()) { curent = 0; }
				else { curent++; }
				break;
			case Key_Enter:
				system("CLS");
				PrintRep(Report::rep[idsrep[curent]]);
				//return curent;
			case Key_q:
				showursor();
				system("CLS");
				return;
				//return curent;
			}
			system("CLS");
		}
	}
}
int CabUsers() {
	std::string punkt[4] { "Меню групп","Создать репорт","Репорты","Выход" };
	for (;;) {
		switch (MenuMain(punkt, 4)) {
		case 0:
			Test::getIDGroupsUsers(Users::UserID, Test::Groups);
			system("CLS");
			break;
		case 1:
			Report::rep.addItem(); Report::CreateRep(Users::usr[Users::UserID].login, GetVal::getCharStr("Введите ваш вопрос > ", 50), GetVal::getCharStr("Введите имя репорта > ", 256), Report::rep[Report::rep.getBackIndex()]);
			system("CLS");
			break;
		case 2:
			RepMenu();
			system("CLS");
			break;
		case 3:
			system("CLS");
			saveall();
			return 0;
		}
	}
}
//=================
void CMDbash();
void CabAdmin();
void initCMD();
MyMap CMD(initCMD);
void editusr() { Users::editUser(Users::getUserGUI()); }
void getanswerreport() { RepMenu(); }
void loadtestingroup() { 
	int grpind = Test::Group::getIDgroup(Test::Groups); if (grpind == -1) { return; }
	Test::Groups[grpind]->LoadTestGroup(GetVal::getValString("Введите имя файла в который сохраняли > "));
}//
void getstaticuser() { Test::getStaticUser(Users::getUserGUI(), Test::Groups); }
void getstaticusers() { Array::ArrayClass<int>x = Users::getInputUsersGUI(); for (int i = 0; i < x.getSize(); i++) Test::getStaticUser(x[i], Test::Groups); }
void creategroup() { Test::Groups.addItem(new Test::Group()); }
void createtestgroup() { 
	int grpind = Test::Group::getIDgroup(Test::Groups); if (grpind == -1) { return; }
	Test::Groups[grpind]->CreateTestGroup();
}
void addusersgroup() { 
	int grpind = Test::Group::getIDgroup(Test::Groups); if (grpind == -1) { return; }
	Test::Groups[grpind]->addUserGroup(Users::getUserGUI()); 
}
void dellusergroup() {
	int grpind = Test::Group::getIDgroup(Test::Groups); if (grpind == -1) { return; }
	Test::Groups[grpind]->dellUserGroup(Users::getUserGUI());
}
void deleteusers() {
	int delUSRID = Users::getUserGUI();
	for (int i = 0; i < Test::Groups.getSize(); i++) {
		if (*Test::Groups[i] == Users::usr[delUSRID].login) { Test::Groups[i]->dellUserGroup(delUSRID); }
	}
	Users::usr.delItemIndex(delUSRID);
}
void editgroup() {
	int groupID = Test::Group::getIDgroup(Test::Groups); if (groupID == -1) { return; }
	Test::Groups[groupID]->rename();
}
void clear() { system("CLS"); }
void extraexit() { exit(112); }
void relog() { 
	if (Users::Auntification() != 0) { exit(3); }
	if (Users::usr[Users::UserID].Admins != true) { exit(CabUsers()); }//Users
	else {
		CMDbash(); exit(0);
	}//adm
}
void deletegroup() {
	int groupID = Test::Group::getIDgroup(Test::Groups); if (groupID == -1) { return; }
	Test::Groups.delItemIndex(groupID);
}
void dellTestGroup() {
	int groupID = Test::Group::getIDgroup(Test::Groups); if (groupID == -1) { return; }
	int TestID = Test::Groups[groupID]->GetTestIDGUI(); if (TestID == -1) { return; }
	Test::Groups[groupID]->deleteTest(TestID);
}
void help() {
	for (int i = 0; i < CMD.getCom().getSize() - 1; i++) {
		WordColor("Команда: ", Black, LightRed, Black, LightGray); std::cout<<std::setiosflags(std::ios::left) << std::setw(16) << CMD.getCom().getArr()[i] << " |";
		WordColor("Описание: ", Black, Green, Black, LightGray); std::cout << CMD.getOpc().getArr()[i] << std::endl;
	}
}
void whome() { Users::printUsrID(Users::UserID); }
void getTestInfo() {
	int groupID = Test::Group::getIDgroup(Test::Groups); if (groupID == -1) { return; }
	int TestID = Test::Groups[groupID]->GetTestIDGUI(); if (TestID == -1) { return; }
	Test::Groups[groupID]->GetStaticTest(TestID);
}
void startUserBash() {
	CabUsers();
}
void edittest() {
	int groupID = Test::Group::getIDgroup(Test::Groups); if (groupID == -1) { return; }
	int TestID = Test::Groups[groupID]->GetTestIDGUI(); if (TestID == -1) { return; }
	Test::Groups[groupID]->EditTest(TestID);
}
void SystemBash() {
	for (std::string inp;;) {
		WordColor("Sys-=# ", Black, LightRed, Black, LightBlue); std::getline(std::cin, inp); //std::transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
		if (inp == "exit") { return; }
		system(inp.c_str());
	}
}

void initCMD() {
	CMD.addElem("getusers", Users::PrintUser,"Вывод информации о нескольких пользователей.");//Вывод информации о нескольких пользователей 1
	CMD.addElem("getstaticuser", getstaticuser, "Статистика пользователя.");//Статистика пользователя 2
	CMD.addElem("getstaticusers", getstaticusers, "Статистика пользователей.");//Статистика пользователей 3
	CMD.addElem("getalluserid", Users::PrintIDUsersGUI, "Вывесть текущие ИД пользователей.");//Вывесть текущие  ИД пользователей 4
	CMD.addElem("editusr", editusr, "Редактировать пользователя.");//Редактировать пользователя 5
	CMD.addElem("getanswerreport", getanswerreport, "Ответ на репорт.");//Ответ на репорт 6
	CMD.addElem("creategroup", creategroup, "Создать группу.");//Создать группу 7 
	CMD.addElem("createtestsave", Test::CreateSaveTest, "Создать тест для дальнейшей загрузки.");//Создать тест для дальнейшей загрузки 8
	CMD.addElem("loadtestingroup", loadtestingroup, "Загрузить тест из сохранёных тестов.");//Загрузить тест из сохранёных тестов 9
	CMD.addElem("createuser", Users::CreateUser, "Создать пользователя.");//Создать пользователя 10
	CMD.addElem("startuser", startUserBash, "Запустить меню ученика.");//Запустить меню ученика 11
	CMD.addElem("createtestgroup", createtestgroup, "Создать тест для группы.");//Создать тест для  группы 12
	CMD.addElem("delltestgroup", dellTestGroup, "Удалить тест из группы.");//Удалить тест из группы. 13
	CMD.addElem("deletegroup", deletegroup, "Удалить группу.");//Удалить группу 14
	CMD.addElem("deleteusers", deleteusers, "Удалить пользователя.");//Удалить пользователя 15
	CMD.addElem("editgroup", editgroup, "Редактировать группу.");//Редактировать группу 16
	CMD.addElem("edittest", edittest, "Редактировать тест в группе.");//Редактировать тест в группе 17
	CMD.addElem("getstatictest", getTestInfo, "Статиситка по тесту в группе.");//Статиситка по тесту в группе 18
	CMD.addElem("dellusergroup", dellusergroup, "Удалить  пользователя из группы.");//Удалить  пользователя из группы 19
	CMD.addElem("addusersgroup", addusersgroup, "Добавить пользователя в группу.");//Добавить пользователя в группу 20
	CMD.addElem("saveusers", saveusers, "Сохранить пользователей");//Сохранить пользователей 21
	CMD.addElem("savegroup", savegroup, "Сохранить группы.");//Сохранить группы 22
	CMD.addElem("savereport", savereport, "Сохранить репорты.");//Сохранить репорты 23
	CMD.addElem("saveall", saveall, "Сохранить всё.");//Сохранить всё 24
	CMD.addElem("loadusers", loadusers, "Загрузить пользователей.");//Загрузить пользователей 25
	CMD.addElem("loadgroup", loadgroup, "Загрузить группы.");//Загрузить группы 26
	CMD.addElem("loadreport", loadreport, "Загрузить репорты.");//Загрузить репорты 27
	CMD.addElem("deletedatabases", DeleteDataBase, "Удалить все базы данных.");//Удалить все базы данных 28
	CMD.addElem("startsysbash", SystemBash, "Командная строка Windows.");//Загрузить всё 30
	CMD.addElem("relog", relog, "Войти в новую учётную запись");// 32
	CMD.addElem("showcursor", showursor, "Показать курсор.");//Показать курсор 33
	CMD.addElem("hidecursor", hidecursor, "Скрыть курсор.");//Скрыть курсор 34
	CMD.addElem("extraexit", extraexit, "Екстренный выход.");//Екстренный выход 35
	CMD.addElem("whome", whome, "Информация о текущем пользоватетле.");//Информация о текущем пользоватетле 35
	CMD.addElem("loadall", saveall, "Загрузить всё.");//Загрузить всё 29
	CMD.addElem("lazymenu", CabAdmin, "Графическое меню.");//Графическое меню
	CMD.addElem("clear", clear, "Очистка комадной строки.");//Очистка комадной строки 
	CMD.addElem("help", help);//Информация о комнадах
	//Удаление пользователя / Удаление пользователя из группы / Удаление группы +++      +
	//Удаление теста из группы / Редактировка Группы / Редактировка теста в группе / Очситка БД ++++    +
	//Статистика по тесту / Игра / (Удаление репорта после просмотра) +       -
}

void CMDbash() {
	for (std::string inp;;) {
		WordColor("ConsoleVERv1.0-=> ", Black, LightRed, Black, LightBlue); std::getline(std::cin, inp); std::transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
		if (inp == "exit") { saveall(); WordColor("", Black, LightRed); return; }
		CMD.cmd(inp);
	}
}
//=================

void CabAdmin() {
	Array::ArrayClass<std::string>pnkt;
	for (int i = 0; i < CMD.getSize()-4; i++) {
		pnkt.addItem(CMD.getComi(i));
	}
	pnkt.addItem("Выход");
	for (int inp;;) {
		inp = MenuMain(pnkt);// MenuMain(pnkt.getArr(), pnkt.getSize());
		if (inp == pnkt.getBackIndex()) { return; }
		else { CMD.getFunc(inp)(); }
		system("pause");
	}
	return;
}



//=================
int start() {
	if (Users::Load() != 0||Users::usr.getSize()<1){
		Users::CreateUser(); Users::getAdminsRulesID(Users::usr.getBackIndex());saveusers();
		return start();
	}
	loadall();
	if (Users::Auntification() != 0) { return 3; }
	if (Users::usr[Users::UserID].Admins != true) { return CabUsers(); }//Users
	else {CMDbash(); return 0; }//adm
}
//=================