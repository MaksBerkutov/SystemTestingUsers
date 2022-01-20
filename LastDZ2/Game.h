#pragma once
#include"MapWork.h"
#include<iostream>
#include<thread>
enum Parties {
	Up,
	Down,
	Left,
	Right
};
class Display {
public:
	static void OutputMap(Maps mp) {
		system("CLS");
		for (const auto& i : mp.GetThisMap()) {
			for (int j = 0; j < i.length(); ++j) {
				if (i[j] == mp.GetDesignations()[5])WordColor(i[j], Black, Green);
				else if (i[j] == mp.GetDesignations()[6])WordColor(i[j], Black, Red);
				else if (i[j] == mp.GetDesignations()[7])
					WordColor(i[j], Black, Yellow);
				else WordColor(i[j], Black, DarkGray);
			}
			std::cout << std::endl;
		}
	}
};
class Person {
protected:
	Maps CurMap;
	struct Cord {
		int x_pos, y_pos;
	};
	Cord CurCordPers;
	int hp = 3;
public:
	bool CheckPosPers(Parties par) {
		for (int i = 0; i < 6; ++i) {
			switch (par) {
			case Up:
				if (CurMap.GetThisMap()[CurCordPers.x_pos + 1][CurCordPers.y_pos] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Down:
				if (CurMap.GetThisMap()[CurCordPers.x_pos - 1][CurCordPers.y_pos] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Left:
				if (CurMap.GetThisMap()[CurCordPers.x_pos][CurCordPers.y_pos + 1] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Right:
				if (CurMap.GetThisMap()[CurCordPers.x_pos][CurCordPers.y_pos - 1] == CurMap.GetDesignations()[i]) return false;
				else break;
			}
		}
		return true;
	}
	void ReloadPosPers(Parties par) {
		CurMap.GetThisMap()[CurCordPers.x_pos][CurCordPers.y_pos] = ' ';
		setCursorPosition(CurCordPers.x_pos, CurCordPers.y_pos); std::cout << ' ';
		switch (par) {
		case Up: CurCordPers.x_pos++; break;
		case Down: CurCordPers.x_pos--; break;
		case Left: CurCordPers.y_pos++; break;
		case Right: CurCordPers.y_pos--; break;
		}
		CurMap.GetThisMap()[CurCordPers.x_pos][CurCordPers.y_pos] = CurMap.GetDesignations()[5];
		setCursorPosition(CurCordPers.x_pos, CurCordPers.y_pos); WordColor(CurMap.GetDesignations()[5], Black, Green);
	}
};
class Enemy : protected Person {
protected:
	int CurColEnem;
	std::vector<Cord> CurCordEnem;
	std::vector<char> Old;
public:
	bool CheckPos(Parties par, int index_enem) {
		for (int i = 0; i < 6; ++i) {
			switch (par) {
			case Up:
				if (CurMap.GetThisMap()[CurCordEnem[index_enem].x_pos + 1][CurCordEnem[index_enem].y_pos] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Down:
				if (CurMap.GetThisMap()[CurCordEnem[index_enem].x_pos - 1][CurCordEnem[index_enem].y_pos] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Left:
				if (CurMap.GetThisMap()[CurCordEnem[index_enem].x_pos][CurCordEnem[index_enem].y_pos + 1] == CurMap.GetDesignations()[i]) return false;
				else break;
			case Right:
				if (CurMap.GetThisMap()[CurCordEnem[index_enem].x_pos][CurCordEnem[index_enem].y_pos - 1] == CurMap.GetDesignations()[i]) return false;
				else break;
			}
		}
		return true;
	}
	Parties GetNewParties(Parties Par) {
		switch (Par) {
		case Up: return Down;
		case Down: return Left;
		case Left: return Right;
		case Right: return Up;
		}
	}
	void ReloadMapEnum(int index_enem, int old_x, int old_y) {
		if (CurMap.GetThisMap()[CurCordEnem[index_enem].x_pos][CurCordEnem[index_enem].y_pos] != CurMap.GetDesignations()[7]) {
			CurMap.GetThisMap()[old_x][old_y] = ' ';
			setCursorPosition(old_x, old_y); std::cout << ' ';
			setCursorPosition(CurCordEnem[index_enem].x_pos, CurCordEnem[index_enem].y_pos);  WordColor(CurMap.GetDesignations()[6], Black, Red);
		}

	}
	void changepos(Parties par, int index_enem) {
		for (int i = 0; i < 4; ++i) {
			switch (par) {
			case Up:
				if (CheckPos(par, index_enem) == true) { CurCordEnem[index_enem].x_pos++; ReloadMapEnum(index_enem, CurCordEnem[index_enem].x_pos - 1, CurCordEnem[index_enem].y_pos); return; }
				else return changepos(GetNewParties(par), index_enem);
				break;
			case Down:
				if (CheckPos(par, index_enem) == true) { CurCordEnem[index_enem].x_pos--; ReloadMapEnum(index_enem, CurCordEnem[index_enem].x_pos + 1, CurCordEnem[index_enem].y_pos); return; }
				else return changepos(GetNewParties(par), index_enem);
				break;
			case Left:
				if (CheckPos(par, index_enem) == true) { CurCordEnem[index_enem].y_pos++; ReloadMapEnum(index_enem, CurCordEnem[index_enem].x_pos, CurCordEnem[index_enem].y_pos - 1); return; }
				else return changepos(GetNewParties(par), index_enem);
				break;
			case Right:
				if (CheckPos(par, index_enem) == true) { CurCordEnem[index_enem].y_pos--; ReloadMapEnum(index_enem, CurCordEnem[index_enem].x_pos, CurCordEnem[index_enem].y_pos + 1); return; }
				else return changepos(GetNewParties(par), index_enem);
				break;
			}
		}
	}
};
class Games final : protected Enemy {
	int th_set = 0; int point = 0;
	void HodEnem(int& th_set) {
		for (; th_set== 0 ;) {

				for (int i = 0; i < CurCordEnem.size(); ++i) {
					changepos(static_cast<Parties>(0 + rand() % 3), i);
				}
				Sleep(150);
			
		}
	}
	void CheckExit(int& th_set) {
		for (; th_set == 0;) {
			
			for (int i = 0; i < CurCordEnem.size(); ++i) {
				if (CurCordEnem[i].x_pos == CurCordPers.x_pos && CurCordEnem[i].y_pos == CurCordPers.y_pos) { th_set = 2; }
			}
		}
		
	}
	void CheckPoint(int&th_set) {
		for (; th_set == 0;) {
			if (CurMap.GetThisMap()[CurCordPers.x_pos][CurCordPers.y_pos] == CurMap.GetDesignations()[7]) {
				point--;
				if (point == 0) { th_set = 1; }

			}
			
		}
	}
	std::vector<int> StartGame() {
		std::vector<int> hod; hod.push_back(0);
		Display::OutputMap(CurMap);
		hidecursor();
		std::thread hodenem(&Games::HodEnem, this,std::ref(th_set)); 
		std::thread checklose(&Games::CheckExit, this, std::ref(th_set)); 
		std::thread checkpoint(&Games::CheckPoint, this, std::ref(th_set)); 
		for (;;) {
			if (th_set != 0) {
				hodenem.join();
				checklose.join();
				checkpoint.join();
				hod.push_back(th_set);
				break;
			}
			switch (_getch()) {
			case Key_Up:
				if (CheckPosPers(Down) == true) { ReloadPosPers(Down); }
				break;
			case Key_Down:
				if (CheckPosPers(Up) == true) { ReloadPosPers(Up); }
				break;
			case Key_Left:
				if (CheckPosPers(Right) == true) { ReloadPosPers(Right); }
				break;
			case Key_Right:
				if (CheckPosPers(Left) == true) { ReloadPosPers(Left); }
				break;
			}
			hod[0]++;
		}return hod;

	}
	void DisplayRes(time_t end,std::vector<int> inf,time_t start) {
		system("CLS");
		std::cout << "Start: " << start << "\nEnd: " << end << "\nHod: " << inf[0] << "\nRes: "<<inf[1] << std::endl;
	}
public:
	Games() {}
	Games(std::string MapName) {
		MapJson mj;
		CurMap.Maps::Maps(mj.getMap(MapName));
		if (CurMap.GetThisMap().size() <= 2) { exit(112); }
		Cord tmp;
		for (int i = 0; i < CurMap.GetThisMap().size(); ++i) {
			for (int j = 0; j < CurMap.GetThisMap()[i].size(); ++j) {
				if (CurMap.GetThisMap()[i][j] == CurMap.GetDesignations()[5]) {
					CurCordPers.x_pos = i; CurCordPers.y_pos = j;
				}
				else if (CurMap.GetThisMap()[i][j] == CurMap.GetDesignations()[6]) {
					CurColEnem++;
					tmp.x_pos = i; tmp.y_pos = j;
					CurCordEnem.push_back(tmp);
				}
			}
		}
		Old.resize(CurCordEnem.size()); Old = { ' ' };
		for (int i = 0; i < CurMap.GetThisMap().size(); ++i) {
			for (int j = 0; j < CurMap.GetThisMap()[i].length(); ++j) {
				if (CurMap.GetThisMap()[i][j] == CurMap.GetDesignations()[7])point++;
			}
		}
		DisplayRes(time(NULL), StartGame(), time(NULL));
		
	}

};
