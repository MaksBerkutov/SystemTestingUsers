#pragma once
#include<iostream>
#include<iomanip>
#include"ArrayClass.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

enum ButtonPrees {
	Key_Up = 72,
	Key_Down = 80,
	Key_Left = 75,
	Key_Right = 77,
	Key_Enter = 13,
	Key_Plus = 61,
	Key_Minus = 45,
	Key_End = 79,
	Key_Ctrl_End = 117,
	Key_q = 8
};
enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void hidecursor()
{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

}
void showursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
template <typename T>
void WordColor(T words, ConsoleColor word_background_color, ConsoleColor word_text_color, ConsoleColor next_background_color = Black, ConsoleColor next_text_color = LightGray)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((word_background_color << 4) | word_text_color));
	std::cout << words;
	SetConsoleTextAttribute(hConsole, (WORD)((next_background_color << 4) | next_text_color));
}

void createGrafic(float num, float all) {
	int prc = num / all * 100;
	if (prc < 10) { WordColor("|          |", Black, Green); return; }
	WordColor("|", Black, Green,Black,Red);
	for (int i = 0; i<10;i++) {
		prc -= 10;
		if (prc>-5||prc>0) {
			std::cout << "#";
		}
		else { std::cout << " "; }
	}
	WordColor("|", Black, Green);
}




int MenuMain(Array::ArrayClass<std::string> str,std::string Arrow="  >") {
	system("CLS");
	int curent = 0;
	for (curent = 0;;) {
		hidecursor();
		system("CLS");
		if (str.getSize() > 20) {

			int _i, _end;
			for (int i = 0, end = 5; i < str.getSize(); i += 5, end += 5) {
				if (curent >= i && curent < end) {
					_i = i; _end = end; break;
				}
			}
			for (int i = _i; i < _end; i++) {
				if (i == curent) { WordColor("\t\t| ", Black, Blue, Black, White); std::cout << (Arrow + str[i]) <<"  |" << curent << "/" << str.getSize() - 1 << std::endl; }
				else { WordColor("\t\t| ", Black, Blue, Black, Red); std::cout << str[i] << std::endl; }
			}
		}
		else {
			for (int i = 0; i < str.getSize(); i++) {
				if (i == curent) { WordColor("\t| ", Black, Blue, Black, White); std::cout << (Arrow + str[i]) << std::endl; }
				else { WordColor("\t| ", Black, Blue, Black, Red); std::cout << str[i] << std::endl; }
			}
		}
		switch (_getch()) {
		case Key_Up:
			if (curent == 0) { curent = str.getBackIndex(); }
			else { curent--; }
			break;
		case Key_Down:
			if (curent == str.getBackIndex()) { curent = 0; }
			else { curent++; }
			break;
		case Key_Enter:
			system("CLS");
			showursor();
			return curent;
		}
		system("CLS");
	}
}
//int MenuMain(std::string* str,int size, std::string Arrow = ">") {
//	system("CLS");
//	for (int curent = 0;;) {
//		for (int i = 0; i < size; i++) {
//			if (i == curent) { WordColor("\t| ", Black, Blue, Black, White); std::cout << (Arrow + str[i]) << std::endl; }
//			else { WordColor("\t| ", Black, Blue, Black, Red); std::cout << str[i] << std::endl; }
//		}
//		switch (_getch()) {
//		case Key_Up:
//			if (curent == 0) { curent = size-1; }
//			else { curent--; }
//			break;
//		case Key_Down:
//			if (curent == size-1) { curent = 0; }
//			else { curent++; }
//			break;
//		case Key_Enter:
//			system("CLS");
//			return curent;
//		}
//		system("CLS");
//	}
//}
int MenuMain(std::string* str, int size, std::string Arrow = ">") {
	system("CLS");
	hidecursor();
	HANDLE hWndConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo);
	int widht = (consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1) * 40 / 100;
	int height = (consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1) * 40 / 100;
	int MaxLenghtStr = 0;
	for (int i = 0; i < size; i++) {
		if ((Arrow + str[i]).length() > MaxLenghtStr) {MaxLenghtStr = (Arrow + str[i]).length();}
	}
	for (int curent = 0;;) {
		std::cout << std::setw(height)<<std::setfill('\n')<<""<< std::setfill(' ');
		//for (int i = 0; i < height; i++) { std::cout << std::endl; }
		std::cout << std::setw(widht)<<"";
		WordColor("#", Black, Blue, Black, Blue); std::cout << std::setw(MaxLenghtStr+2) << std::setfill('=') << "#" << std::setfill(' ')<< std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << std::setw(widht) << "";
			if (i == curent) { WordColor("| ", Black, Blue, Black, White); std::cout << std::setw(MaxLenghtStr) << (Arrow + str[i]); }
			else { WordColor("| ", Black, Blue, Black, Red); std::cout << std::setw(MaxLenghtStr) << str[i]; }
			WordColor("|\n", Black, Blue);
		}
		std::cout << std::setw(widht+1);
		WordColor("#", Black, Blue, Black, Blue); std::cout << std::setw(MaxLenghtStr + 2) << std::setfill('=') << "#" << std::setfill(' ') << std::endl;
		switch (_getch()) {
		case Key_Up:
			if (curent == 0) { curent = size - 1; }
			else { curent--; }
			
			break;
		case Key_Down:
			if (curent == size - 1) { curent = 0; }
			else { curent++; }
			break;
		case Key_Enter:
			system("CLS");
			showursor();
			return curent;
		}
		system("CLS");
	}
}
