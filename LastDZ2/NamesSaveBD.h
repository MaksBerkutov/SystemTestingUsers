#pragma once
#include<iostream>
//Здесь храняться имена всех файлов и папок.
namespace savename {
	static std::string NameSaveUsers = "Users.bin";//Имя файла сохранения пользователей 
	static std::string NameSaveGroup = "Group.bin";//Имя файла сохранения групп 
	static std::string NameSaveReport = "Report.bin";//Имя файла сохранения репортов 
	static std::string NameSaveHash = "system.dll";//Имя файла сохранения хешов всех файлов 
	static std::string NameSaveTestFile = "test.file";//Имя файла сохранения тестов для загрузки 
}
namespace dirsavename {
	static std::string dirSave = "BD\\";//Имя корневой папки
}


