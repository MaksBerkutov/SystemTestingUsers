#pragma once
#include"ArrayClass.h"
#include <functional>
#include<tuple>
class MyMap {
	Array::ArrayClass<std::string>command;
	Array::ArrayClass<std::string>opicanie;
	Array::ArrayClass<std::function<void()>>fun;
	void sorts() {
		for (int i = 0; i < command.getSize()-1; i++) {
			for (int j = 0; j < command.getSize()-1 - i - 1; j++) {
				if (command[j] > command[j + 1]) {
					std::tuple<std::string, std::string, std::function<void()>>tmp = std::make_tuple(command[j], opicanie[j], fun[j]);
					command[j] = command[j + 1];
					opicanie[j] = opicanie[j + 1];
					fun[j] = fun[j + 1];
					command[j + 1] = std::get<0>(tmp);
					opicanie[j + 1] = std::get<1>(tmp);
					fun[j + 1] = std::get<2>(tmp);
				}
			}
		}
	}
public:
	
	
	MyMap(std::function<void()> init) { init(); sorts(); }
	int getSize() { return opicanie.getSize(); }
	Array::ArrayClass<std::string>& getCom() { return command; }
	std::string getComi(int i) { return command[i]; }
	Array::ArrayClass<std::string>& getOpc() { return opicanie; }
	std::string getOpci(int i) { return opicanie[i]; }
	std::function<void()>& getFunc(int i) { return fun[i]; }
	void addElem(std::string cmd, std::function<void()> _one, std::string opc = "Нет описания!") {
		this->command.addItem(cmd);this->opicanie.addItem(opc);
		this->fun.addItem(_one);
	}
	void cmd(std::string name) {
		for (int i = 0; i < command.getSize(); i++) {
			if (command[i] == name) { fun[i](); return; }
		}
		std::cout << "Команда не найдена!\nhelp для помощи!" << std::endl;
	}
};
