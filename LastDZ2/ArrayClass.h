#pragma once
#include<iostream>
namespace Array {
	template<typename T>
	class ArrayClass
	{
		T* arr;
		int size;
	public:
		ArrayClass() {
			
			size = 0;
			arr = nullptr;
		}
		ArrayClass(int _size) {
			size = _size;
			arr = new T[size];
			for (int i = 0; i < size; i++) { this->arr[i] = rand() % 100; }
		}
		ArrayClass(T* _arr, int _size) {
			size = _size;
			arr = new T[size];
			for (int i = 0; i < size; i++) { this->arr[i] = _arr[i]; }
		}
		ArrayClass(ArrayClass&& x) {
			size = x.size;
			arr = new T[size];
			for (int i = 0; i < size; i++) { this->arr[i] = x.arr[i]; }
			x.arr = nullptr; x.size = NULL;
		}
		ArrayClass(const ArrayClass& x) {
			arr = new T[x.size];
			size = x.size;
			for (int i = 0; i < size; i++) { arr[i] = x.arr[i]; }
		}
		ArrayClass (ArrayClass& x) {
			arr = new T[x.getSize()];
			size = x.getSize();
			for (int i = 0; i < size; i++) { arr[i] = x.arr[i]; }
		}
		ArrayClass operator=(ArrayClass&& x) {
			size = x.size;
			if (arr != nullptr)arr = nullptr;
			arr = new T[size];
			for (int i = 0; i < size; i++) { this->arr[i] = x.arr[i]; }
			x.arr = nullptr; x.size = NULL;
			return*this;
		}
		ArrayClass operator=(ArrayClass& x) {
			if (x.arr == nullptr) {
				arr = nullptr; size = 0;
			}
			else {
				size = x.size;
				if (arr != nullptr)arr = nullptr;
				arr = new T[size];
				for (int i = 0; i < size; i++) { this->arr[i] = x.arr[i]; }
				return*this;
			}

		}
		T& operator[](int ind) { return arr[ind]; }
		int getSize() { return this->size; }
		int getBackIndex() { return this->size - 1; }
		void setSize(int i) {
			size = i;
			arr = new T[size];
		}
		T* getArr() { return arr; }
		T*& getArrAdress() { return arr; }
		int& getSizeAdress() { return size; }
		void addItem() {
			T* tmp = new T[size];
			for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
			arr = nullptr;
			arr = new T[++size];
			for (int i = 0; i < size - 1; i++) { arr[i] = tmp[i]; }
		}
		void delItem() {
			T* tmp = new T[size];
			for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
			arr = nullptr;
			arr = new T[--size];
			for (int i = 0; i < size; i++) { arr[i] = tmp[i]; }
		}
		void addItemIndex(int index) {
			if (index >= 0 && index < size) {
				T* temp = new T[size + 1];
				for (int i = 0, j = 0; i < size; i++, j++)
				{
					if (i == index) {j++; }
					temp[j] = arr[i];
				}

				delete[] arr;
				size++;
				arr = temp;
			}

		}
		void delItemIndex(int index) {
			if (index >= 0 && index < size) {
				T* tmp = new T[size];
				for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
				arr = nullptr;
				arr = new T[--size];
				for (int i = 0; i < size; i++) {
					if (i < index) arr[i] = tmp[i];
					else arr[i] = tmp[i + 1];
				}
			}
		}
		void operator= (bool flg) {
			if (flg != 1) {
				arr = nullptr;
				size = 0;
			}
		}
		void addItem(T var) {
			T* tmp = new T[size];
			for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
			arr = nullptr;
			arr = new T[++size];
			for (int i = 0; i < size - 1; i++) { arr[i] = tmp[i]; }
			arr[size - 1] = var;
		}
		void delItem(T var) {
			T* tmp = new T[size];
			for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
			arr = nullptr;
			arr = new T[--size];
			for (int i = 0; i < size; i++) { arr[i] = tmp[i]; }
			arr[size - 1] = var;
		}
		void addItemIndex(int index, T var) {
			if (index >= 0 && index < size) {
				T* temp = new T[size + 1];
				for (int i = 0, j = 0; i < size; i++, j++)
				{
					if (i == index) { temp[j] = var; j++; }
					temp[j] = arr[i];
				}

				delete[] arr;
				size++;
				arr = temp;
				/*T* tmp = new T[size];
				for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
				arr = nullptr;
				arr = new T[++size];
				for (int i = 0; i < size - 1; i++) {
					if (i < index) arr[i] = tmp[i];
					else if (i==index)arr[i] = var;
					else arr[i + 1] = tmp[i];
				}*/
			}
		}
		void delItemIndex(int index, T var) {
			if (index >= 0 && index < size) {
				T* tmp = new T[size];
				for (int i = 0; i < size; i++) { tmp[i] = arr[i]; }
				arr = nullptr;
				arr = new T[--size];
				for (int i = 0; i < size; i++) {
					if (i < index) arr[i] = tmp[i];
					else arr[i] = tmp[i + 1];
				}
				arr[size - 1] = var;
			}
		}
		void reloadItemIndex(T num, int index) { arr[index] = num; }
		int minItem() {
			int res = 0;
			for (int i = 1; i < size; i++) {
				if (arr[res] < arr[i]) { res = i; }
			}
			return res;
		}
		int maxItem() {
			int res = 0;
			for (int i = 1; i < size; i++) {
				if (arr[res] > arr[i]) { res = i; }
			}
			return res;
		}
		void sortMin() {
			T b = NULL;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[j] > arr[j + 1]) {
						b = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = b;
					}
				}
			}
		}
		void sortMax() {
			T b = NULL;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[j] < arr[j + 1]) {
						b = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = b;
					}
				}
			}
		}
		void ClearArr() {
			arr = nullptr;
			size = 0;
		}
		void DeleteArrayManual() {
			delete[] arr;
		}
		//~ArrayClass() {  }
	};
}
