#pragma once
#include<iostream>
#include"Menuh.h"
#include<string>
namespace GetVal {
	int getValInt(std::string str) {
		WordColor(str, Black, LightGreen, Black, Red);
	    int num; std::cin >> num;
		return num;
	}
	float getValFloat(std::string str) {
		WordColor(str, Black, LightGreen, Black, Red); float num; std::cin >> num;
		return num;
	}
	std::string getValString(std::string str) {
		WordColor(str, Black, LightGreen, Black, Red); std::string num; std::getline(std::cin,num);
		return num;
	}
	char* getCharStr(std::string str, int BufSize) {
		char* res = new char[BufSize];
		WordColor(str, Black, LightGreen, Black, Red); std::cin.getline(res, BufSize); return res;
	}
}