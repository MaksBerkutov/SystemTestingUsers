#pragma once
#include"ArrayClass.h"
#include<fstream>
#include<string>
#define Output 0
namespace ChekerFile {
	bool CheckFileSave(std::string path) {
		std::fstream file; file.open(path, std::ios::in);
		if (file.is_open()) {
			int tmpInt; std::string tmpString;
			file >> tmpInt; file.ignore(); std::getline(file, tmpString);
#if Output==1
			std::cout << "Name test: " << tmpString << std::endl;
#endif
			if (tmpInt <= 1 || file.eof()) { file.close(); return false; }
			for (int i = 0, n = tmpInt,boolsize = 0,intsize = 0; i < n; i++){
				if (file.eof()) { file.close(); return false; }
				std::getline(file, tmpString);
#if Output==1
				std::cout <<i<< ") Answer: " << tmpString << std::endl;
#endif
				file >> intsize; file >> boolsize; file.ignore();
				if(intsize!= boolsize) { file.close(); return false; }
				for (int j = 0; j < intsize; ++j) {
					if (file.eof()) { file.close(); return false; }
					std::getline(file, tmpString);
#if Output==1
					std::cout <<"\t" << j << ") Answer options: " << tmpString << std::endl;
#endif
				}
				for (int j = 0; j < boolsize; ++j) {
					if (file.eof()) { file.close(); return false; }
					file >> tmpInt;
					if(0<tmpInt&&tmpInt>1) { file.close(); return false; }
#if Output==1
					tmpString = tmpInt == 0 ? "False" : "True";
					std::cout << "\t " << j << ") Answer options: " << tmpString << std::endl;
#endif
				}
				file.ignore();
			}return true;
		}
		file.close(); return false;
	}
}