#pragma once
#include<iostream>
#define DEBUG 0//��������� ����� �������
namespace MyStack {
	template<typename T>
	class Structs {
		template<typename T>
		class Dates {
		public:
			T data;//��������
			Dates* pNext;//��������� �� ��������� ������
			Dates* pPrev;//��������� �� ���������� ������
		public:
			//�����������
			Dates(T Val = T(), Dates* pN = nullptr, Dates* pP = nullptr) {
				this->data = Val; this->pNext = pN; this->pPrev = pP;
			}
		};
		Dates<T>* pHead;//��������� �� ������ �����
		Dates<T>* pEnd;//��������� �� ����� �����
		int size = 0;//������ �����
	public:
		//������ ������� ������� �����
		int getSize() { return size; }
		int getBackIndex() { return size - 1; }
#if DENUG == 1
		void checkEnd() {
			Dates<T>* tmp = pEnd;
			while (tmp != nullptr) {
				cout << tmp->data << endl;
				if (tmp->pPrev == nullptr)cout << "NULLPTR" << endl;
				tmp = tmp->pPrev;
			}
		}
		void checkFront() {
			Dates<T>* tmp = pHead;
			while (tmp != nullptr) {
				cout << tmp->data << endl;
				if (tmp->pNext == nullptr)cout << "NULLPTR" << endl;
				tmp = tmp->pNext;
			}
		}
		void stat() {
			cout << pHead->data << " " << pEnd->data << endl;
		}
#endif
		//����������� �� ���������
		Structs() {
			pHead = nullptr; pEnd = nullptr;
		}
		//����������� �� ���������
		Structs(T val) {
			pHead = new Dates<T>(val, pHead);
			pEnd = pHead;
			size++;
		}
		//���������� � ������
		void pushFront(T val) {
			if (pHead == nullptr) {
				pHead = new Dates<T>(val, pHead); pEnd = pHead;
				size++;
			}
			else {
				if (pEnd == pHead) {
					pHead = new Dates<T>(val, pHead);
					pEnd->pPrev = pHead;
					size++;
				}
				else {
					Dates<T>* tmp = pHead;
					pHead = new Dates<T>(val, pHead);
					tmp->pPrev = pHead;
					size++;
				}
			}
		}
		//���������� � �����
		void pushBack(T val) {
			if (pHead == nullptr) {
				pushFront(val);
			}
			else {
				pEnd->pNext = new Dates<T>(val, nullptr, pEnd);
				pEnd = pEnd->pNext;
				size++;
			}
		}
		//�������� � ������
		T& pop_front() {
			if (pHead != nullptr) {
				T tmp = pHead->data;
				pHead = pHead->pNext;
				pHead->pPrev = nullptr;
				size--;
				return tmp;
			}
		}
		//�������� � �����
		T& pop_end() {
			if (pHead != nullptr) {
				T tmp = pEnd->data;
				pEnd = pEnd->pPrev;
				pEnd->pNext = nullptr;
				size--;
				return tmp;
			}
		}
		//�������� �� �������
		void dellItem(int index) {
			if (index == 0) {
				pop_front();
				return;
			}
			else if (index == size - 1) {
				pop_end();
				return;
			}
			else if (index >= 0 && index < size) {
				Dates<T>* tmp = this->pHead;
				for (int i = 0; i < size; i++) {
					if (i < index - 1) tmp = tmp->pNext;
					else if (i == (index - 1)) {
						Dates<T>* y = tmp->pNext;
						tmp->pNext = y->pNext;
						break;
					}
				}
				size--;
			}
		}
		//���������� �� �������
		void addItem(T val, int index) {
			if (index == 0) {
				pushFront(val);
				return;
			}
			else if (index == size - 1) {
				pushBack(val);
				return;
			}
			else if (index >= 0 && index < size) {
				Dates<T>* tmp = this->pHead;
				for (int i = 0; i < size; i++) {
					if (i < index - 1) tmp = tmp->pNext;
					else if (i == (index - 1)) {
						Dates<T>* x = tmp;
						Dates<T>* y = tmp->pNext;
						tmp = new Dates<T>(val);
						x->pNext = tmp; tmp->pNext = y;
						//delete[]x; delete[]y;
						break;
					}
				}
				size++;
			}
		}
		//��������� �����
		void deleteAll() { pHead = nullptr, pEnd = nullptr; size = 0; }
		//���� ������
		T& operator[](int ind) {
			if (ind >= 0 && ind < size) {
				Dates<T>* tmp = this->pHead;
				for (int i = 0; i < size; i++) {
					if (i != ind) {
						tmp = tmp->pNext;
					}
					else {
						return tmp->data;
					}
				}
			}
		}
		//����� ���������� � ����� 
		int sceartchVariable(T old) {
			for (int i = 0; i < size; i++) {
				if (operator[](i) == old) { return i; }
			}
		}
		//������������� ostream (<<)
		friend std::ostream& operator<<(std::ostream& os, Structs& ls)
		{
			for (int i = 0; i < ls.size; i++) {
				os << "|" << i << "\t" << ls[i] << std::endl;
			}
			return os;
		}


	};
}

