#pragma once
#include"md5.h"
#include<string>
#include<fstream>

std::string getHash(std::string path) {
	std::fstream File; File.open(path, std::ios::in); std::string tmp;
	if (File.is_open()) {
		while (!File.eof()) {
			File >> path; tmp += path;
		}
		File.close();
		return md5(tmp);
	}
	File.close();
	return path;
}
