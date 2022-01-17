#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <direct.h>
#include <iostream>
void CreateDirectory_(std::string str) {
	if (_mkdir(str.c_str()) == -1);
}
