#pragma once
#include"ArrayClass.h"
#include"MySteck.h"
#include"Menuh.h"
#include"Users.h"
#include<fstream>
#include <filesystem>
#include <experimental/filesystem> 
//Как это работает вкраце
/*
\\==================Manual========================>
*----------\ 
*  TestName \--------------->|Имя теста|
*----------------------#-------------->|Блок теста|
*		Vopros1--------|------------------------->|Вопрос блока теста|	
*			1)Otvet1-0-|-------------------------------------------->|Пункт ответа блока теста|
*			2)Otvet2 0-|---------------------------------------------------------------------->|True\Flase пункт ответа блока теста|				  
*			3)Otvet3 1 |				  
*			n)Otvetn 0 |				  #------------------------------------------------------------------------------------------#
*----------------------#----------------->|Мы видим что наши тест модульный тоесть есть один вопрос и похожие "блоки" тестов!        |
*		Voprosn		   |				  |Класс Answer Отвечает за те самые блоки тестов,а класс Test хранит массив блоков Answer и |
*			1)Otvet1 0 |				  |Имя теста                                                                                 |
*			2)Otvet2 1 |				  #------------------------------------------------------------------------------------------#
*			3)Otvet3 0 |
*			n)Otvetn 0 |
*----------------------#
*                       \
*                        \
*                         \ 
*                          \
*                           \
*                            \
*                             #-------------------------------------<Group>--------------------------------------------#
*                             |В свою очередь класс Group позволяет нам созадвать уникальные груупы с разными юзерами  |
*                             |1) В каждой группе разные тесты														   |
*                             |2) Юзер может состоять в разный группах												   |
*                             #----------------------------------------------------------------------------------------#
*
//=============================================================================================>
*/
namespace Test {
	class Group;
	//Класс тестов
	class Test {
	protected:
		friend int Load(Array::ArrayClass<Group*>& C);
		friend int Save(Array::ArrayClass<Group*>C);
		friend class Group;
		//Класс блоков
		class Answers {
			friend int Load(Array::ArrayClass<Group*>& C);
			friend int Save(Array::ArrayClass<Group*>C);
			friend class Group;
		public:
			Array::ArrayClass<std::string> AnswerOptions;
			Array::ArrayClass<bool> AnswerOptionsTrueFalse;
			std::string Answer;
			Answers() {};
			void CreateAnswer() {
				WordColor("Введите вопрос > ", Black, LightRed, Black, LightBlue); std::getline(std::cin, Answer);
				system("CLS");
				Array::ArrayClass<std::string>punkt;
				punkt.addItem("Добавить ответ");
				punkt.addItem("Выход");
				Array::ArrayClass<std::string>punkt2;
				punkt2.addItem("Вариант ответа ложен");
				punkt2.addItem("Вариант ответа правдив");
				for (bool flg = false; flg != true;) {
					switch (MenuMain(punkt)) {
					case 0:
						WordColor("Введите вариант ответа > ", Black, LightRed, Black, LightBlue); AnswerOptions.addItem(); std::getline(std::cin, AnswerOptions[AnswerOptions.getBackIndex()]);
						AnswerOptionsTrueFalse.addItem(); AnswerOptionsTrueFalse[AnswerOptionsTrueFalse.getBackIndex()] = MenuMain(punkt2);
						break;
					case 1:
						system("CLS");
						flg = !flg;
						break;
					}
				}
			}
			void EditTest() {
				Array::ArrayClass<std::string>punkt2;
				punkt2.addItem("Вариант ответа ложен");
				punkt2.addItem("Вариант ответа правдив");
				for (int CurID = 0;;) {
					system("CLS");
					hidecursor();
					WordColor(("\t\t\t" + Answer + "\n\n"), Black, Blue);
					for (int i = 0; i < AnswerOptions.getSize(); i++) {
						if (i == CurID) {
							WordColor("\t\t+ ", Black, White);
							if (AnswerOptionsTrueFalse[i] != true)WordColor(AnswerOptions[i], Black, Red);
							else WordColor(AnswerOptions[i], Black, Green);
							WordColor(" -\n", Black, White);
						}
						else {
							if (AnswerOptionsTrueFalse[i] != true)WordColor(("\t\t  " + AnswerOptions[i] + "\n"), Black, Red);
							else WordColor(("\t\t  " + AnswerOptions[i] + "\n"), Black, Green);

						}
					}
					switch (_getch()) {
					case Key_Left:
						AnswerOptionsTrueFalse[CurID] = !AnswerOptionsTrueFalse[CurID];
						break;
					case Key_Right:
						AnswerOptionsTrueFalse[CurID] = !AnswerOptionsTrueFalse[CurID];
						break;
					case Key_Plus:
						WordColor("Введите вариант ответа > ", Black, LightRed, Black, LightBlue); AnswerOptions.addItemIndex(CurID); std::getline(std::cin, AnswerOptions[CurID]);
						AnswerOptionsTrueFalse.addItemIndex(CurID); AnswerOptionsTrueFalse[CurID] = MenuMain(punkt2);
						break;
					case Key_Minus:
						if (AnswerOptions.getSize() < 2) {
							system("CLS");
							WordColor("\t\tВопросов не может быть меньше одного!\n", Black, Red);
							system("pause");
							system("CLS");
						}
						else {
							AnswerOptions.delItemIndex(CurID); AnswerOptionsTrueFalse.delItemIndex(CurID);
							if (CurID >= AnswerOptions.getBackIndex())CurID = 0;
						}
						
						break;
					case Key_Up:
						if (CurID == 0)CurID = AnswerOptions.getBackIndex();
						else CurID--;
						break;
					case Key_Down:
						if (CurID == AnswerOptions.getBackIndex())CurID = 0;
						else CurID++;
						break;
					case Key_Enter:
						system("CLS");
						WordColor(("Введите новое значение для " + AnswerOptions[CurID] + " > "), Black, LightBlue, Black, LightRed);
						std::getline(std::cin, AnswerOptions[CurID]);
						break;
					case Key_q:
						return;
						break;
					}
				}
			}
		};
		std::string name;
		Array::ArrayClass<Answers>tests;
	public:
		Array::ArrayClass<std::string> getTruText(int IDAnswer) {
			Array::ArrayClass<std::string> res;
			for (size_t i = 0; i < tests[IDAnswer].AnswerOptionsTrueFalse.getSize(); i++) {
				if (tests[IDAnswer].AnswerOptionsTrueFalse[i] != false) { res.addItem(tests[IDAnswer].AnswerOptions[i]); }
			}
			return res;
		}
		std::string getNameTest() { return name; }
		Test(bool a) {}
		Test(std::string TestName) {//Загрузка теста
			std::fstream file; file.open((dirsavename::dirSave + TestName + "\\" + savename::NameSaveTestFile), std::ios::in);
			if(file.is_open()==false){
				system("CLS");WordColor("\t\tТеста не существует!\n", Black, Red);
				system("pause");system("CLS");return;
			}
			int tmp;
			file >> tmp;  tests.setSize(tmp);
			file.ignore(); std::getline(file, name); //file >> name ;
			for (int i = 0; i < tests.getSize(); file.ignore(),i++) {
				 std::getline(file, tests[i].Answer); //file >> tests[i].Answer;
				file >> tmp; tests[i].AnswerOptions.setSize(tmp);
				file >> tmp; tests[i].AnswerOptionsTrueFalse.setSize(tmp);
				for (int j = 0; j < tests[i].AnswerOptions.getSize(); j++) {
					file.ignore(); std::getline(file, tests[i].AnswerOptions[j]);// file >> tests[i].AnswerOptions[j];
				}
				for (int j = 0; j < tests[i].AnswerOptionsTrueFalse.getSize(); j++) {
					file >> tests[i].AnswerOptionsTrueFalse[j];
				};
			}
			file.close();
		}
		void Save(std::string TestName) {//Cохранение теста
			CreateDirectory_((dirsavename::dirSave + TestName + "\\"));
			std::fstream file; file.open((dirsavename::dirSave + TestName + "\\"+savename::NameSaveTestFile), std::ios::out | std::ios::trunc);
			file << tests.getSize() << std::endl;
			file << name << std::endl;
			for (int i = 0; i < tests.getSize(); i++) {
				file << tests[i].Answer << std::endl;
				file << tests[i].AnswerOptions.getSize() << std::endl;
				file << tests[i].AnswerOptionsTrueFalse.getSize() << std::endl;
				for (int j = 0; j < tests[i].AnswerOptions.getSize(); j++) {
					file << tests[i].AnswerOptions[j] << std::endl;
				}
				for (int j = 0; j < tests[i].AnswerOptionsTrueFalse.getSize(); j++) {
					file << tests[i].AnswerOptionsTrueFalse[j] << std::endl;
				};
			}
			file.close();
		}
		Test() {
			WordColor("Введите имя теста > ", Black, LightRed, Black, LightBlue); std::getline(std::cin, name);
			system("CLS");
			Array::ArrayClass<std::string>punkt;
			punkt.addItem("Добавить вопрос");
			punkt.addItem("Выход");
			for (;;) {
				switch (MenuMain(punkt)) {
				case 0:
					tests.addItem(Answers()); tests[tests.getBackIndex()].CreateAnswer();
					system("pasue");
					break;
				case 1:

					return;
				}
			}

		}

	};
	//Класс грууп
	class Group {
		//============
		friend int Load(Array::ArrayClass<Group*>& C);
		friend int Save(Array::ArrayClass<Group*>C);
		//============
		struct SaveDataBase {
			int GroupID, TestID, CurTest, Trues;
		};
		Array::ArrayClass<Array::ArrayClass<SaveDataBase>>SaveS;//Сохранёные тесты
		Array::ArrayClass<std::string>login;//Логины юзеров который относяться к текущей группе
		Array::ArrayClass<Test*>test;//Тесты текущей группы
		Array::ArrayClass<Array::ArrayClass<Array::ArrayClass<int>>>ResUsers;//Массив ответов тестов кадого пользователя группы
		Array::ArrayClass<Array::ArrayClass<int>>Res;//Оценки
		std::string  NameGroup;
		void _StartTest(int GroupID, int TestID, int CurTest = 0, int Trues = 0) {
			system("CLS");
			if (CurTest == test[TestID]->tests.getSize()) {
				system("CLS");
				if (Trues > 0) { Res[GroupID][TestID] = static_cast<int>(static_cast<float>(Trues) / static_cast<float>(test[TestID]->tests.getSize()) * 100); }
				else { Res[GroupID][TestID] = 0; }
				WordColor(("\tОценка за тест: " + std::to_string(Res[GroupID][TestID]) + "\n"), Black, LightRed, Black, LightBlue);
				system("pause");
				system("CLS");
				showursor();
				return;
			}
			for (int CurAnswer = 0;;) {
				hidecursor();
				WordColor(("\t\t" + test[TestID]->name + " | " + std::to_string(CurTest + 1) + "/" + std::to_string(test[TestID]->tests.getSize()) + "\n\n"), Black, Red);
				WordColor((test[TestID]->tests[CurTest].Answer + " :\n"), Black, LightRed);
				for (size_t i = 0; i < test[TestID]->tests[CurTest].AnswerOptions.getSize(); i++) {
					WordColor(("\t" + std::to_string(i + 1) + ") "), Black, Blue);
					if (i == CurAnswer) { WordColor((test[TestID]->tests[CurTest].AnswerOptions[i] + "\n"), Black, White); }
					else { WordColor((test[TestID]->tests[CurTest].AnswerOptions[i] + "\n"), Black, LightGreen); }
				}
				switch (_getch()) {
				case Key_Up:
					if (CurAnswer == 0) { CurAnswer = test[TestID]->tests[CurTest].AnswerOptions.getBackIndex(); }
					else { CurAnswer--; }
					break;
				case Key_Down:
					if (CurAnswer == test[TestID]->tests[CurTest].AnswerOptions.getBackIndex()) { CurAnswer = 0; }
					else { CurAnswer++; }
					break;
				case Key_Enter:
					ResUsers[GroupID][TestID].addItem(CurAnswer);
					if (test[TestID]->tests[CurTest].AnswerOptionsTrueFalse[CurAnswer] != true) { return _StartTest(GroupID, TestID, ++CurTest, Trues); }
					else { return _StartTest(GroupID, TestID, ++CurTest, ++Trues); }
				case Key_q:
					Res[GroupID][TestID] = -2;
					SaveS[GroupID][TestID].CurTest = CurTest;
					SaveS[GroupID][TestID].GroupID = GroupID;
					SaveS[GroupID][TestID].TestID = TestID;
					SaveS[GroupID][TestID].Trues = Trues;
					showursor();
					return;
					break;
				}
				system("CLS");
			}

		}
		void PrintResAnswerGUILogic(int GroupID, int TestID) {
			/*
							  NameTest {LightRed}
					1){Blue} Vopros{Cyan}: VariantOtveta |{White} True{Green}
					2){Blue} Vopros{Cyan}: VariantOtveta |{White} False{Red} ({White} True{LightGreen} ,{White} True{LightGreen} ){White}
					Result:{LightGrean} XX{LightGrey} /{White} 100%{LightRed}
			*/
			Array::ArrayClass<std::string>tmp;
			system("CLS");
			WordColor(("\t\t" + test[TestID]->name + "\n"), Black, LightRed);
			for (size_t i = 0; i < test[TestID]->tests.getSize(); i++) {
				WordColor(("\t" + std::to_string(i + 1) + ") "), Black, Blue);
				WordColor((test[TestID]->tests[i].Answer + ": "), Black, Cyan);
				WordColor((test[TestID]->tests[i].AnswerOptions[ResUsers[GroupID][TestID][i]]), Black, LightRed);
				WordColor(" | ", Black, White);
				if (test[TestID]->tests[i].AnswerOptionsTrueFalse[ResUsers[GroupID][TestID][i]] != true) {
					WordColor("False ", Black, Red);
					WordColor("( ", Black, White);
					tmp = test[TestID]->getTruText(i);
					for (size_t i = 0; i < tmp.getSize(); i++) {
						WordColor(tmp[i], Black, Green);
						if (i + 1 < tmp.getSize()) {
							WordColor(" , ", Black, White);
						}
					}
					WordColor(")\n", Black, White);
				}
				else { WordColor("True\n", Black, Green); }
			}
			WordColor("Result: ", Black, LightGreen);
			WordColor(std::to_string(Res[GroupID][TestID]), Black, LightGray);
			WordColor(" / ", Black, White); WordColor("100%\n", Black, LightRed);
			system("pause");
			system("CLS");
			tmp.DeleteArrayManual();//???????
		}
		void PrintSaveAnswerGUILogic(int GroupID, int TestID) {
		/*
			 NameTest {LightRed}
					1){Blue} Vopros{Cyan}: VariantOtveta |{White} True{Green}
					2){Blue} Vopros{Cyan}: VariantOtveta |{White} False{Red} ({White} True{LightGreen} ,{White} True{LightGreen} ){White}
					Result:{LightGrean} XX{LightGrey} /{White} 100%{LightRed}
		
		*/
			Array::ArrayClass<std::string>tmp;
			system("CLS");
			WordColor(("\t\t" + test[TestID]->name + "\n"), Black, LightRed);
			for (size_t i = 0; i < test[TestID]->tests.getSize(); i++) {
				if (i < ResUsers[GroupID][TestID].getSize()) {
					WordColor(("\t" + std::to_string(i + 1) + ") "), Black, Blue);
					WordColor((test[TestID]->tests[i].Answer + ": "), Black, Cyan);
					WordColor((test[TestID]->tests[i].AnswerOptions[ResUsers[GroupID][TestID][i]]), Black, LightRed);
					WordColor(" | ", Black, White);
					if (test[TestID]->tests[i].AnswerOptionsTrueFalse[ResUsers[GroupID][TestID][i]] != true) {
						WordColor("False ", Black, Red);
						WordColor("( ", Black, White);
						tmp = test[TestID]->getTruText(i);
						for (size_t j = 0; j < tmp.getSize(); j++) {
							WordColor(tmp[i], Black, Green);
							if (i + 1 < tmp.getSize()) {
								WordColor(" , ", Black, White);
							}
						}
						WordColor(")\n", Black, White);
					}
					else { WordColor("True\n", Black, Green); }
				}
				else {
					WordColor(("\t" + std::to_string(i + 1) + ") "), Black, Blue);
					WordColor((test[TestID]->tests[i].Answer + ": "), Black, Cyan);
					WordColor("Не давлася ответ!\n", Black, White);
				}
			}
			WordColor("Result: ", Black, LightGreen);
			WordColor(std::to_string(ResUsers[GroupID][TestID].getSize()), Black, LightGray);
			WordColor(" / ", Black, White); WordColor((std::to_string(test[TestID]->tests.getSize())), Black, LightRed);
			system("pause");
			system("CLS");
			tmp.DeleteArrayManual();//???????
		}
	public:
		std::string getNameSGroup() { return NameGroup; }
		Group() {
			WordColor("Введите имя группы > ", Black, LightRed, Black, LightBlue); std::getline(std::cin, NameGroup);
			Array::ArrayClass<int>IDGroup = Users::getInputUsersGUI();
			for (size_t i = 0; i < IDGroup.getSize(); i++) {
				login.addItem(Users::usr[IDGroup[i]].login); ResUsers.addItem(); Res.addItem(); SaveS.addItem();
			}
		}
		void rename() {
			WordColor("Введите новое имя группы > ", Black, LightRed, Black, LightBlue); std::getline(std::cin, NameGroup);
		}
		//для выделения памяти в сис-ме загрузки!
		Group(bool a) {}
		//Получение ид в группе по ид пользователя
		int GetGroupID(int RealID) {
			for (int i = 0; i < login.getSize(); i++) {
				if (strcmp(login[i].c_str(), Users::usr[RealID].login) == 0) { return i; }
			}
			return -1;
		}
		//Добавление пользователя в группу
		void addUserGroup(int UsrID) {
			for (int i = 0; i < login.getSize(); i++) {
				if (strcmp(Users::usr[UsrID].login, login[i].c_str()) == 0) {
					WordColor("\t\tПользователь уже есть в группе!\n", Black, Red);
					return;
				}
			}
			login.addItem(Users::usr[UsrID].login); ResUsers.addItem(); Res.addItem(); SaveS.addItem();
			for (int i = 0; i < test.getSize(); i++) {
				ResUsers[ResUsers.getBackIndex()].addItem();
				Res[ResUsers.getBackIndex()].addItem();
				SaveS[ResUsers.getBackIndex()].addItem();

			}
		}
		
		void dellUserGroup(int UserID) {
			int GroupID = GetGroupID(UserID);
			if (GroupID<0) {
				system("CLS");
				WordColor("\t\tПользователь нет в группе!\n", Black, Red);
				system("pause");
				system("CLS");
				return;
			}
			login.delItemIndex(GroupID); ResUsers.delItemIndex(GroupID); Res.delItemIndex(GroupID); SaveS.delItemIndex(GroupID);
		}
		//Создание теста для группы
		void CreateTestGroup() {
			test.addItem(new Test());
			if (test[test.getBackIndex()]->tests.getSize() < 2) {
				system("CLS");
				WordColor("\t\tВопросов не может быть меньше двух!\n", Black, Red);
				system("pause");
				system("CLS");
				test.delItemIndex(test.getBackIndex());
			}
			else {
				for (size_t i = 0; i < login.getSize(); i++) {
					ResUsers[i].addItem();
					Res[i].addItem();
					SaveS[i].addItem();
				}
			}
		}
		//Выбор, вывод всех тестов в группе для текущего юзера
		void GroupTestMenu() {
			int GroupID = GetGroupID(Users::UserID); if (GroupID < 0) { return; }
			if(test.getSize()<1){
				system("CLS");
				WordColor("\t\tТестов нет!\n", Black, Red);
				system("pause");
				system("CLS");
				return;
			}
			for (int CurID = 0;;) {
				hidecursor();
				system("CLS");
				WordColor(("\t"+NameGroup+"\n"), Black, Blue);
				for (int i = 0; i < test.getSize(); i++) {
					WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
					if (Res[GroupID][i] >= 0&& Res[GroupID][i] <= 100) {
						i == CurID ? WordColor(test[i]->name, Black, White) : WordColor(test[i]->name, Black, Blue);
						WordColor(" | ", Black, White);
						WordColor("Пройден", Black, Red);
						WordColor(" (", Black, White);
						WordColor(std::to_string(Res[GroupID][i]), Black, Green);
						WordColor("/", Black, White);
						WordColor("100", Black, Red);
						WordColor(")\n", Black, White);
					}
					else if (Res[GroupID][i] == -2) {
						i == CurID ? WordColor(test[i]->name, Black, White) : WordColor(test[i]->name, Black, Blue);
						WordColor(" | ", Black, White);
						WordColor("Cохранён\n", Black, Red);
					}
					else {
						i == CurID ? WordColor(test[i]->name, Black, White) : WordColor(test[i]->name, Black, Blue);
						WordColor(" | ", Black, White);
						WordColor("Не пройден\n", Black, Red);
					}
				}
				switch (_getch()) {
				case Key_Up:
					if (CurID == 0) { CurID = test.getBackIndex(); }
					else { CurID--; }
					break;
				case Key_Down:
					if (CurID == test.getBackIndex()) { CurID = 0; }
					else { CurID++; }
					break;
				case Key_Enter:
					if (Res[GroupID][CurID] >= 0 && Res[GroupID][CurID] <= 100) { PrintResAnswerGUILogic(GroupID, CurID); }
					else if (Res[GroupID][CurID] == -2) { _StartTest(SaveS[GroupID][CurID].GroupID, SaveS[GroupID][CurID].TestID, SaveS[GroupID][CurID].CurTest, SaveS[GroupID][CurID].Trues); }
					else {
						_StartTest(GroupID, CurID);
					}
					system("CLS");
					break;
				case Key_q:
					showursor();
					system("CLS");
					return ;
					
				}
			}
			/*
			\n \t
			 WordColor(")\n",Black,Blue);
				NameGroup{}
					1{} ){} TestFirst{} |{} Пройден{} ({} result{} ){}
					2{} ){} Test2{} |{} Не пройден{}
					3{} ){} Test3{} |{} Сохранён{} ({} 3{} /{} 12{} ){}
			
			*/
		}
		//Загрузка теста из заранее созданого файла!
		void LoadTestGroup(std::string name) {
			test.addItem(new Test(name));
			if (test[test.getBackIndex()]->tests.getSize() < 2) test.delItemIndex(test.getBackIndex());
			else {
				for (size_t i = 0; i < login.getSize(); i++) {
					ResUsers[i].addItem();
					Res[i].addItem();
					SaveS[i].addItem(SaveDataBase());
				}
			}
		}
		
		int GetTestIDGUI() {
			if (test.getSize() < 1) {
				system("CLS");
				WordColor("\t\tТестов нет!\n", Black, Red);
				system("pause");
				system("CLS");
				return -1;
			}
			for (int CurID = 0;;) {
				hidecursor();
				system("CLS");
				for (size_t i = 0; i < test.getSize(); i++) {
					WordColor(("\t"+std::to_string(i + 1) + ") "), Black, Blue);
					if (CurID == i) {
						WordColor(test[i]->getNameTest(), Black, White);
					}
					else {
						WordColor(test[i]->getNameTest(), Black, Red);
					}
					std::cout << std::endl;
				}
				switch (_getch()) {
				case Key_Up:
					if (CurID == 0) { CurID = test.getBackIndex(); }
					else { CurID--; }
					break;
				case Key_Down:
					if (CurID == test.getBackIndex()) { CurID = 0; }
					else { CurID++; }
					break;
				case Key_Enter:
					showursor();
					system("CLS");
					return CurID;
				}
			}

		}
		void deleteTest(int testID) {
			test.delItemIndex(testID);
			for (size_t i = 0; i < login.getSize(); i++) {
				ResUsers[i].delItemIndex(testID);
				Res[i].delItemIndex(testID);
				SaveS[i].delItemIndex(testID);
			}
		}
		void EditTest(int TestID) {
			bool edit = false;
			for (int CurID = 0;;) {
				system("CLS");
				hidecursor();
				WordColor(("\t\t\t" + test[TestID]->name + "\n\n"), Black, Green);
				for (int i = 0; i < test[TestID]->tests.getSize(); i++) {
					if (i == CurID) {
						WordColor(("\t\t+ " + test[TestID]->tests[i].Answer + " -\n"), Black, White);
					}
					else {
						WordColor(("\t\t  " + test[TestID]->tests[i].Answer + "\n"), Black, Red);
					}
				}
				switch (_getch()) {
				case Key_Plus:
					edit = true;
					test[TestID]->tests.addItemIndex(CurID,Test::Answers()); test[TestID]->tests[CurID].CreateAnswer();
					break;
				case Key_Minus:
					edit = true;
					if (test[TestID]->tests.getSize() < 2) {
						system("CLS");
						WordColor("\t\tВопросов не может быть меньше двух!\n", Black, Red);
						system("pause");
						system("CLS");
					}
					else { 
						test[TestID]->tests.delItemIndex(CurID); 
						if (CurID >= test[TestID]->tests.getBackIndex())CurID = 0;
					}
					break;
				case Key_Up:
					if (CurID == 0)CurID = test[TestID]->tests.getBackIndex();
					else CurID--;
					break;
				case Key_Ctrl_End:
					WordColor(("Введите новое значение для " + test[TestID]->name + " > "), Black, LightBlue, Black, LightRed);
					std::getline(std::cin, test[TestID]->name);
					break;
				case Key_End:
					WordColor(("Введите новое значение для " + test[TestID]->tests[CurID].Answer + " > "), Black, LightBlue, Black, LightRed);
					std::getline(std::cin, test[TestID]->tests[CurID].Answer);
					break;
				case Key_Down:
					if (CurID == test[TestID]->tests.getBackIndex())CurID = 0;
					else CurID++;
					break;
				case Key_Enter:
					edit = true;
					test[TestID]->tests[CurID].EditTest();
					break;
				case Key_q:
					if (edit == true) {
						for (size_t i = 0; i < login.getSize(); i++) {
							ResUsers[i][TestID].ClearArr();
							Res[i][TestID] = -10;
						}
					}
					return;
					break;
				}
			}
		}
		void GetStaticTest(int TestID) {
			int TestСompleted = 0;
			int TestSaved = 0; float AverageScore = 0;
			Array::ArrayClass<int>ans; for (int i = 0; i < test[TestID]->tests.getSize(); i++) { ans.addItem(0); }
			for (int i = 0; i < login.getSize(); i++) { 
				if (Res[i][TestID] >= 0) { 
					TestСompleted++; AverageScore += Res[i][TestID];
					for (int j = 0; j < test[TestID]->tests.getSize(); j++) {
						if (test[TestID]->tests[j].AnswerOptionsTrueFalse[ResUsers[i][TestID][j]] != true) { ans[j]--; }
						else { ans[j]++; }
					}
				} 
				else if (Res[i][TestID] == -2) { TestSaved++; } 
			}
			TestСompleted > 0 ? AverageScore /= TestСompleted : AverageScore = 0;
			int TestNotPass = login.getSize() - (TestСompleted + TestSaved);
			int AnswerIDMostErrors = 0;
			int AnswerIDLeastErrors = 0;
			for (int i = 1; i < ans.getSize(); i++) {
				if (ans[i] > ans[AnswerIDMostErrors]) { AnswerIDMostErrors = i; }
				if (ans[i] < ans[AnswerIDLeastErrors]) { AnswerIDLeastErrors = i; }
			}
			WordColor(("\t\t"+test[TestID]->name + "\n\n"), Black, Cyan);
			WordColor("Прошли тест      ", Black, Cyan); createGrafic(TestСompleted, login.getSize()); WordColor((" (" + std::to_string(TestСompleted) + "/" + std::to_string(login.getSize()) + ")\n"), Black, White);
			WordColor("Не прошли тест   ", Black, Cyan); createGrafic(TestNotPass, login.getSize()); WordColor((" (" + std::to_string(TestNotPass) + "/" + std::to_string(login.getSize())+")\n"), Black, White);
			WordColor("Сохранили тест   ", Black, Cyan); createGrafic(TestSaved, login.getSize()); WordColor((" (" + std::to_string(TestSaved) + "/" + std::to_string(login.getSize())+")\n"), Black, White);
			WordColor("Средний бал тест ", Black, Cyan); createGrafic(AverageScore, 100); WordColor((" (" + std::to_string(static_cast<int>(AverageScore)) + "%/" + "100%)\n"), Black, White);
			if(TestNotPass == login.getSize()){ WordColor("Все тесты не cданны!\n", Black, Red); }
			else if(AnswerIDLeastErrors == AnswerIDMostErrors){ WordColor("Все тесты cданны на 100%\n", Black, Cyan); }
			else {
				WordColor("Тест на котором меньше все-го ошибались: ", Black, Cyan, Black, Green); std::cout << test[TestID]->tests[AnswerIDLeastErrors].Answer<<std::endl;
				WordColor("Тест на котором больше все-го ошибались: ", Black, Cyan, Black, Red); std::cout << test[TestID]->tests[AnswerIDMostErrors].Answer<<std::endl;
				WordColor("", Black, Cyan);
			}
		}
		void PrintResAnswerGUI(int IDuser = Users::UserID) {
			int GroupID = GetGroupID(IDuser); if (GroupID < 0) { return; }
			int CurID = 0;
			Array::ArrayClass<int>res;
			for (size_t i = 0; i < test.getSize(); i++) {
				if (Res[GroupID][i] >= -2) { res.addItem(i); }
			}
			if (res.getSize() <= 0) { system("CLS"); WordColor("\t\tУ даного пользователя тесты ещё не сдавались!\n", Black, Red); system("pause"); system("CLS"); return; }
			for (bool flag = false; flag != true;) {
				hidecursor();
				system("CLS");
				for (size_t i = 0; i < res.getSize(); i++) {
					WordColor((std::to_string(i + 1) + ") "), Black, Blue);
					if (CurID == i) {
						WordColor(test[res[i]]->getNameTest(), Black, White);
					}
					else {
						WordColor(test[res[i]]->getNameTest(), Black, Red);
					}
					std::cout << std::endl;
				}
				switch (_getch()) {
				case Key_Up:
					if (CurID == 0) { CurID = res.getBackIndex(); }
					else { CurID--; }
					break;
				case Key_Down:
					if (CurID == res.getBackIndex()) { CurID = 0; }
					else { CurID++; }
					break;
				case Key_Enter:
					if (Res[GroupID][CurID]!=-2)PrintResAnswerGUILogic(GroupID, res[CurID]); 
					else PrintSaveAnswerGUILogic(GroupID, res[CurID]); 
					system("CLS");
					break;
				case Key_q:
					flag = !flag;
					system("CLS");
					showursor();
					return;
					break;
				}
			}
		}
		//Получить ИД интересуемой группы из массива групп
		static int getIDgroup(Array::ArrayClass<Group*>& res){
			if (res.getSize() < 1) { system("CLS"); WordColor("\t\tНет групп!\n", Black, Red); system("pause"); system("CLS");  return -1; }
			for (int CurID = 0;;) {
				hidecursor();
				system("CLS");
				for (int i = 0; i < res.getSize(); i++) {
					WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
					i == CurID ? WordColor(res[i]->NameGroup, Black, White) : WordColor(res[i]->NameGroup, Black, Blue);
					std::cout << std::endl;
				}
				switch (_getch()) {
				case Key_Up:
					if (CurID == 0) { CurID = res.getBackIndex(); }
					else { CurID--; }
					break;
				case Key_Down:
					if (CurID == res.getBackIndex()) { CurID = 0; }
					else { CurID++; }
					break;
				case Key_Enter:
					showursor();
					return CurID;
					break;
				}
			}
		}
		/*Trash*/void StartTest() {
			int GroupID = GetGroupID(Users::UserID); if (GroupID < 0) { return; }
			int TestID = GetTestIDGUI(); if (TestID < 0) { return; }
			_StartTest(GroupID, TestID);
		}
		//Проверка принадлежит ли юзер к этой группе(по логину)
		bool operator==(char x[33]) {
			for (size_t i = 0; i < login.getSize(); i++) {
				if (strcmp(login[i].c_str(), x) == 0) { return true; }
			}
			return false;
		}
		/*void KYSTADDMEMEORYDEBAGIINGS() {//Дебагг функция была
			for (size_t i = 0; i < login.getSize(); i++) {
				SaveS.addItem();
				for (size_t j = 0; j < login.getSize(); j++) { SaveS[i].addItem(); }
			}
		}*/
	};
	//===========Сохранения <?> Доработка
	int Save(Array::ArrayClass<Group*>C) {
		std::fstream file;
		file.open((dirsavename::dirSave+savename::NameSaveGroup), std::ios::out | std::ios::binary | std::ios::trunc);
		file << C.getSize() << std::endl;
		for (int i = 0; i < C.getSize(); i++) {
			
			file << C[i]->login.getSize() << std::endl;
			file << C[i]->test.getSize() << std::endl;
			file << C[i]->NameGroup << std::endl;
			for (int j = 0; j < C[i]->login.getSize(); j++) {
				file << C[i]->login[j] << std::endl;
			}
			for (int j = 0; j < C[i]->test.getSize(); j++) {
				file << C[i]->test[j]->tests.getSize() << std::endl;
				file << C[i]->test[j]->name << std::endl;
				for (int _j = 0; _j < C[i]->test[j]->tests.getSize(); _j++) {
					file << C[i]->test[j]->tests[_j].AnswerOptions.getSize() << std::endl;
					file << C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.getSize() << std::endl;
					file << C[i]->test[j]->tests[_j].Answer << std::endl;
					for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptions.getSize(); i_j++) {
						file << C[i]->test[j]->tests[_j].AnswerOptions[i_j] << std::endl;
					}
					for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.getSize(); i_j++) {
						file << C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse[i_j] << std::endl;
					}
				}
			}
			file << C[i]->Res.getSize() << std::endl;
			for (int j = 0; j < C[i]->Res.getSize(); j++) {
				file << C[i]->Res[j].getSize() << std::endl;
				for (int _j = 0; _j < C[i]->Res[j].getSize(); _j++) {
					file << C[i]->Res[j][_j] << std::endl;
				}
			}
			file << C[i]->ResUsers.getSize() << std::endl;
			for (int j = 0; j < C[i]->ResUsers.getSize(); j++) {
				file << C[i]->ResUsers[j].getSize() << std::endl;
				for (int _j = 0; _j < C[i]->ResUsers[j].getSize(); _j++) {
					file << C[i]->ResUsers[j][_j].getSize() << std::endl;
					for (int i_j = 0; i_j < C[i]->ResUsers[j][_j].getSize(); i_j++) {
						file << C[i]->ResUsers[j][_j][i_j] << std::endl;
					}
				}
			}
			file << C[i]->SaveS.getSize() << std::endl;
			for (int j = 0; j < C[i]->SaveS.getSize(); j++) {
				file << C[i]->SaveS[j].getSize() << std::endl;
				for (int _j = 0; _j < C[i]->SaveS[j].getSize(); _j++) {
					file << C[i]->SaveS[j][_j].CurTest << std::endl;
					file << C[i]->SaveS[j][_j].GroupID << std::endl;
					file << C[i]->SaveS[j][_j].TestID << std::endl;
					file << C[i]->SaveS[j][_j].Trues << std::endl;
				}
			}
		}
		file.close();
		return 0;
	}
	//int Load(Array::ArrayClass<Group*>& C) {
	//	std::fstream file;
	//	file.open((dirsavename::dirSave + savename::NameSaveGroup), std::ios::in | std::ios::binary);
	//	int tmp;
	//	file >> tmp; for (int i = 0; i < tmp; i++)C.addItem(new Group(true));
	//	for (int i = 0; i < C.getSize(); i++) {
	//		file >> tmp; C[i]->login.setSize(tmp);
	//		file >> tmp; for (int j = 0; j < tmp; j++) { C[i]->test.addItem(new Test(true)); }
	//		file >> C[i]->NameGroup;
	//		for (int j = 0; j < C[i]->login.getSize(); j++) {
	//			file >> C[i]->login[j];
	//		}
	//		for (int j = 0; j < C[i]->test.getSize(); j++) {
	//			file >> tmp; C[i]->test[j]->tests.setSize(tmp);
	//			file >> C[i]->test[j]->name;
	//			for (int _j = 0; _j < C[i]->test[j]->tests.getSize(); _j++) {
	//				file >> tmp; C[i]->test[j]->tests[_j].AnswerOptions.setSize(tmp);
	//				file >> tmp; C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.setSize(tmp);
	//				file >> C[i]->test[j]->tests[_j].Answer;
	//				for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptions.getSize(); i_j++) {
	//					file >> C[i]->test[j]->tests[_j].AnswerOptions[i_j];
	//				}
	//				for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.getSize(); i_j++) {
	//					file >> C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse[i_j];
	//				}
	//			}
	//		}
	//		file >> tmp; C[i]->Res.setSize(tmp);
	//		for (int j = 0; j < C[i]->Res.getSize(); j++) {
	//			file >> tmp; C[i]->Res[j].setSize(tmp);
	//			for (int _j = 0; _j < C[i]->Res[j].getSize(); _j++) {
	//				file >> C[i]->Res[j][_j];
	//			}
	//		}
	//		file >> tmp; C[i]->ResUsers.setSize(tmp);
	//		for (int j = 0; j < C[i]->ResUsers.getSize(); j++) {
	//			file >> tmp; C[i]->ResUsers[j].setSize(tmp);
	//			for (int _j = 0; _j < C[i]->ResUsers[j].getSize(); _j++) {
	//				file >> tmp; C[i]->ResUsers[j][_j].setSize(tmp);
	//				for (int i_j = 0; i_j < C[i]->ResUsers[j][_j].getSize(); i_j++) {
	//					file >> C[i]->ResUsers[j][_j][i_j];
	//				}
	//			}
	//		}
	//		file >> tmp; C[i]->SaveS.setSize(tmp);
	//		for (int j = 0; j < C[i]->SaveS.getSize(); j++) {
	//			file >> tmp; C[i]->SaveS[j].setSize(tmp);
	//			for (int _j = 0; _j < C[i]->SaveS[j].getSize(); _j++) {
	//				file >> C[i]->SaveS[j][_j].CurTest;
	//				file >> C[i]->SaveS[j][_j].GroupID;
	//				file >> C[i]->SaveS[j][_j].TestID;
	//				file >> C[i]->SaveS[j][_j].Trues;
	//			}
	//		}
	//	}
	//	file.close();
	//	return 0;
	//}
	int Load(Array::ArrayClass<Group*>& C) {
		std::fstream file; char inp[256];
		file.open((dirsavename::dirSave + savename::NameSaveGroup), std::ios::in | std::ios::binary);
		int tmp;
		file >> tmp; for (int i = 0; i < tmp; i++)C.addItem(new Group(true));
		for (int i = 0; i < C.getSize(); i++) {
			file >> tmp; C[i]->login.setSize(tmp);
			file >> tmp; for (int j = 0; j < tmp; j++) {C[i]->test.addItem(new Test(true));}
			file.ignore(); std::getline(file, C[i]->NameGroup);// file >> C[i]->NameGroup;//file.getline(inp, 256); C[i]->NameGroup = inp;  //// 
			for (int j = 0; j < C[i]->login.getSize(); j++) {
				file >> C[i]->login[j]; 
			}
			for (int j = 0; j < C[i]->test.getSize(); j++) {
				file >> tmp; C[i]->test[j]->tests.setSize(tmp);
				file.ignore(); std::getline(file, C[i]->test[j]->name);//file >> C[i]->test[j]->name;
				for (int _j = 0; _j < C[i]->test[j]->tests.getSize(); _j++) {
					file >> tmp; C[i]->test[j]->tests[_j].AnswerOptions.setSize(tmp);
					file >> tmp; C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.setSize(tmp);
					file.ignore(); std::getline(file, C[i]->test[j]->tests[_j].Answer);//file >> C[i]->test[j]->tests[_j].Answer;
					for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptions.getSize(); i_j++) {
						std::getline(file, C[i]->test[j]->tests[_j].AnswerOptions[i_j]);//file >> C[i]->test[j]->tests[_j].AnswerOptions[i_j];
					}
					for (int i_j = 0; i_j < C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse.getSize(); i_j++) {
						file >> C[i]->test[j]->tests[_j].AnswerOptionsTrueFalse[i_j];
					}
				}
			}
			file >> tmp; C[i]->Res.setSize(tmp);
			for (int j = 0; j < C[i]->Res.getSize(); j++) {
				file >> tmp; C[i]->Res[j].setSize(tmp);
				for (int _j = 0; _j < C[i]->Res[j].getSize(); _j++) {
					file >> C[i]->Res[j][_j];
				}
			}
			file >> tmp; C[i]->ResUsers.setSize(tmp);
			for (int j = 0; j < C[i]->ResUsers.getSize(); j++) {
				file >> tmp; C[i]->ResUsers[j].setSize(tmp);
				for (int _j = 0; _j < C[i]->ResUsers[j].getSize(); _j++) {
					file >> tmp; C[i]->ResUsers[j][_j].setSize(tmp);
					for (int i_j = 0; i_j < C[i]->ResUsers[j][_j].getSize(); i_j++) {
						file >> C[i]->ResUsers[j][_j][i_j];
					}
				}
			}
			file >> tmp; C[i]->SaveS.setSize(tmp);
			for (int j = 0; j < C[i]->SaveS.getSize(); j++) {
				file >> tmp; C[i]->SaveS[j].setSize(tmp);
				for (int _j = 0; _j < C[i]->SaveS[j].getSize(); _j++) {
					file >> C[i]->SaveS[j][_j].CurTest;
					file >> C[i]->SaveS[j][_j].GroupID;
					file >> C[i]->SaveS[j][_j].TestID;
					file >> C[i]->SaveS[j][_j].Trues;
				}
			}
		}
		file.close();
		return 0;
	}
	
	//===========\\
	//Статистика пользователя в группах
	void getStaticUser(int IDuser, Array::ArrayClass<Group*>& C) {
		Array::ArrayClass<int> res;
		for (size_t i = 0; i < C.getSize(); i++) {
			if (*C[i] == Users::usr[IDuser].login) { res.addItem(i); }
		}
		if (res.getSize() < 1) {
			system("CLS");
			WordColor("\n\n\t\tПользователя нет ни в одной группе!\n\n", Black, Red);
			system("pause"); system("CLS"); return;
		}
		for (int CurID = 0;;) {
			hidecursor();
			system("CLS");
			WordColor(("\t" + Users::usr[IDuser].NameUsers + "\n"), Black, Blue);
			for (int i = 0; i < res.getSize(); i++) {
				WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
				i == CurID ? WordColor(C[res[i]]->getNameSGroup(), Black, White) : WordColor(C[res[i]]->getNameSGroup(), Black, Blue);
				std::cout << std::endl;
			}
			switch (_getch()) {
			case Key_Up:
				if (CurID == 0) { CurID = res.getBackIndex(); }
				else { CurID--; }
				break;
			case Key_Down:
				if (CurID == res.getBackIndex()) { CurID = 0; }
				else { CurID++; }
				break;
			case Key_Enter:
				C[res[CurID]]->PrintResAnswerGUI(IDuser);
				system("CLS");
				break;
			case Key_q:
				showursor();
				system("CLS");
				return;
				break;

			}
		}

	}
	//Выбор группы
	void getIDGroupsUsers(int IDUser, Array::ArrayClass<Group*>& C) {
		Array::ArrayClass<int> res;
		for (size_t i = 0; i < C.getSize(); i++) {
			if (*C[i] == Users::usr[IDUser].login) { res.addItem(i); }
		}
		if (res.getSize() < 1) {
			system("CLS");
			WordColor("\n\n\t\tПользователя нет ни в одной группе!\n\n", Black, Red); 
			system("pause"); system("CLS");return; 
		}
		for (int CurID = 0;;) {
			hidecursor();
			system("CLS");
			WordColor(("\t" + Users::usr[IDUser].NameUsers + "\n"), Black, Blue);
			for (int i = 0; i < res.getSize(); i++) {
				WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
				i == CurID ? WordColor(C[res[i]]->getNameSGroup(), Black, White) : WordColor(C[res[i]]->getNameSGroup(), Black, Blue);
				std::cout << std::endl;
			}
			switch (_getch()) {
			case Key_Up:
				if (CurID == 0) { CurID = res.getBackIndex(); }
				else { CurID--; }
				break;
			case Key_Down:
				if (CurID == res.getBackIndex()) { CurID = 0; }
				else { CurID++; }
				break;
			case Key_Enter:
				C[res[CurID]]->GroupTestMenu();
				system("CLS");
				break;
			case Key_q:
				showursor();
				system("CLS");
				return;
				break;

			}
		}
		//return res;
	}
	//Выбор ид группы из массива
	int GetIDGroup(Array::ArrayClass<Group*>& C) {		
		for (int CurID = 0;;) {
			hidecursor();
			system("CLS");
			for (int i = 0; i < C.getSize(); i++) {
				WordColor(("\t\t" + std::to_string(i + 1) + ") "), Black, Red);
				i == CurID ? WordColor(C[i]->getNameSGroup(), Black, White) : WordColor(C[i]->getNameSGroup(), Black, Blue);
				std::cout << std::endl;
			}
			switch (_getch()) {
			case Key_Up:
				if (CurID == 0) { CurID = C.getBackIndex(); }
				else { CurID--; }
				break;
			case Key_Down:
				if (CurID == C.getBackIndex()) { CurID = 0; }
				else { CurID++; }
				break;
			case Key_Enter:
				system("CLS");
				showursor();
				return CurID;
				break;
			}
		}
		//return res;
	}
	//Сохранение теста
	void CreateSaveTest() {
		Test tmp; tmp.Save(GetVal::getValString("Ввведите имя теста для сохранения > "));
	}
	static Array::ArrayClass<Group*>Groups;
	
}


