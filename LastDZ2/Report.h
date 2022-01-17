#pragma once
#include<iostream>
#include"ArrayClass.h"
namespace Report {
	struct Info {
		char IDIn[33]; char IDOut[33] = "\0";
		char Name[50]; char MsgIn[256]; char MsgOut[256]="\0";
		
	};
	void CreateRep(char log[33], char MsgIn[256], char Name[50],Info&obj) {
		std::strcpy(obj.IDIn, log); 
		std::strcpy(obj.MsgIn, MsgIn);
		std::strcpy(obj.Name, Name);
	}
	
	//void getReportAnswer(Reports& obj, char log[33]) {
	//	std::strcpy(obj.id[1], log);
	//	WordColor("¬ведите ответ на вопрос ", Black, LightGreen); WordColor(obj.massege[1], Black, Red); WordColor(" > ", Black, LightGreen, Black, LightBlue);
	//	std::getline(std::cin, obj.massege[2]);
	//}
	static Array::ArrayClass<Info>rep;
	int getRepGUI() {
		hidecursor();
		for (int curent = 0;;) {
			for (int i = 0; i < rep.getSize(); i++) {
				if (i == curent) { WordColor("\t|  ", Black, Blue, Black, White); std::cout << rep[i].Name << std::endl; }
				else { WordColor("\t| ", Black, Blue, Black, Red); std::cout << rep[i].Name << std::endl; }
			}
			switch (_getch()) {
			case Key_Up:
				if (curent == 0) { curent = rep.getBackIndex(); }
				else { curent--; }
				break;
			case Key_Down:
				if (curent == rep.getBackIndex()) { curent = 0; }
				else { curent++; }
				break;
			case Key_Enter:
				showursor();
				system("CLS");
				return curent;
			}
			system("CLS");
		}
	}
	Array::ArrayClass<int> getRepsLogin(char log[33]) {
		Array::ArrayClass<int>idsrep;
		for (int i = 0; i < rep.getSize(); i++) {
			if (strcmp(rep[i].IDIn, log) == 0) { idsrep.addItem(i); }
		}
		return idsrep;
	}
	//void OutputRep() {
	//	Reports::getReportAnswer(*rep[getRepGUI()], Users::usr[Users::UserID].login);
	//}
}