#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"directory_set.h"
#include"NamesSaveBD.h"
namespace Save {
    template<typename T>
    int Save(T* array, int size, std::string name) {
        std::fstream file;
        CreateDirectory_(dirsavename::dirSave);
        file.open((dirsavename::dirSave + name), std::ios::out | std::ios::binary);
        if (file.is_open())
        {
            file.write((char*)&size, sizeof(size));        // записать набор байтов размера массива
            file.write((char*)array, size * sizeof(T));  // записать набор байтов массива
            file.close();
        }
        else
        {
            file.close();
            perror("Error occured while opening file");
            return 2;
        }
        file.close();
        return 0;
    }
}
namespace Load {
    template<typename T>
    int Load(T*& array, int& size, std::string name) {
        std::fstream file;
        file.open((dirsavename::dirSave + name), std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.read((char*)&size, sizeof(size));        // считать набор байтов
            array = new T[size]{};
            file.read((char*)array, size * sizeof(T));    // считать набор байтов
            file.close();
        }
        else {
            file.close();
            perror("Error occured while opening file");
            return 1;
        }
        file.close();
        return 0;
    }
}















