#pragma once
#include<vector> 
#include"nlohmann/json.hpp"
#include<string>
#include"Menuh.h"
#include"NamesSaveBD.h"
#include<fstream>
template<typename T>
void GetValue(T& Val, std::string str) {
	WordColor(str, Black, Green, Black, Blue); std::cin >> Val; std::cin.ignore();
}
std::string GetValue(std::string str) {
	WordColor(str, Black, Green, Black, Blue); std::getline(std::cin, str); return str;
}
class Maps {
	friend void CreateMap();
	friend class MapJson;
protected:
	std::vector<std::string> CurMap;
	char injection1; char injection2; char injection3; char injection4;
	char wall; char player; char enemy; char point;
public:
	Maps() {}
	Maps(const Maps& obj) {
		this->injection1 = obj.injection1;
		this->injection2 = obj.injection2;
		this->injection2 = '*';
		this->injection3 = obj.injection3;
		this->injection4 = obj.injection4;
		this->wall = obj.wall;
		this->player = obj.player;
		this->enemy = obj.enemy;
		this->point = obj.point;
		for (const auto& i : obj.CurMap) {
			this->CurMap.push_back(i);
		}
	}
	std::vector<std::string>& GetThisMap() { return CurMap; }
	//0          //1        //2        //3       //4    //5    //6   //7
	std::vector<char> GetDesignations() { return std::vector<char>{injection1, injection2, injection3, injection4, wall, player, enemy, point, ' ' }; }
};
class MapJson {
	std::string Name;
	nlohmann::json object;
public:
	MapJson(std::string Name = dirsavename::dirSave+ savename::NameSaveGameJsonFile) {
		this->Name = Name;
		std::string str, tmp;
		std::fstream file; file.open(Name, std::ios::in);
		if (file.is_open()) {
			while (!file.eof()) {
				std::getline(file, tmp); str += tmp;
			}
		}
		if (!str.empty()) this->object = nlohmann::json::parse(str);
		file.close();
	}
	static std::vector<std::string> GetNameMap() {
		MapJson obj; std::vector<std::string>ret;
		for (const auto& [key, value] : obj.object.items()) {
			ret.push_back(key);
		}return ret;
	}
	std::string InConvertMap(std::vector<std::string>& obj) {
		std::string ret;
		for (const auto i : obj) {
			ret += i + char(1);
		}
		return ret;
	}
	std::vector<std::string> OutConvertMap(std::string obj) {
		std::vector<std::string> ret; std::string tmp;
		for (int i = 0; i < obj.length(); ++i) {
			if (obj[i] == char(1)) { ret.push_back(tmp); tmp = ""; continue; }
			else tmp += obj[i];
		}
		return ret;
	}
	void AddNewMap(std::string NewMapName, Maps& AddMap) {
		AddMap.CurMap.insert(AddMap.CurMap.begin(), "");
		AddMap.CurMap.push_back("");
		for (int i = 0; i < AddMap.CurMap[1].length(); ++i) {
			AddMap.CurMap[0] += AddMap.wall;
			AddMap.CurMap[AddMap.CurMap.size() - 1] += AddMap.wall;
		}

		for (int i = 0; i < AddMap.CurMap.size(); ++i) {
			if (i != 0 || i != AddMap.CurMap.size() - 1) {
				AddMap.CurMap[i].insert(AddMap.CurMap[i].begin(), AddMap.wall);
				AddMap.CurMap[i].insert(AddMap.CurMap[i].end(), AddMap.wall);
			}
		}
		AddMap.CurMap[0][0] = AddMap.injection1; AddMap.CurMap[0][AddMap.CurMap[1].length() - 1] = AddMap.injection2;
		AddMap.CurMap[AddMap.CurMap.size() - 1][0] = AddMap.injection3; AddMap.CurMap[AddMap.CurMap.size() - 1][AddMap.CurMap[1].length() - 1] = AddMap.injection4;
		std::string ConvertsMap = InConvertMap(AddMap.CurMap);
		object[NewMapName] = {
			{"injection1",std::to_string(int(AddMap.injection1))},
			{"injection2",std::to_string(int(AddMap.injection2))},
			{"injection3",std::to_string(int(AddMap.injection3))},
			{"injection4",std::to_string(int(AddMap.injection4))},
			{"wall",std::to_string(int(AddMap.wall))},
			{"player",std::to_string(int(AddMap.player))},
			{"enemy",std::to_string(int(AddMap.enemy))},
			{"point",std::to_string(int(AddMap.point))},
			{"map",ConvertsMap}
		};
	}
	Maps getMap(std::string MapName) {
		Maps ret;
		for (const auto& [key, value] : object.items()) {
			if (MapName == key) {
				ret.injection1 = char(std::stoi(std::string(value["injection1"])));
				ret.injection2 = char(std::stoi(std::string(value["injection2"])));
				ret.injection3 = char(std::stoi(std::string(value["injection3"])));
				ret.injection4 = char(std::stoi(std::string(value["injection4"])));
				ret.player = char(std::stoi(std::string(value["player"])));
				ret.wall = char(std::stoi(std::string(value["wall"])));
				ret.enemy = char(std::stoi(std::string(value["enemy"])));
				ret.point = char(std::stoi(std::string(value["point"])));
				ret.CurMap = OutConvertMap(std::string(value["map"]));

				break;
			}
		}
		return ret;
	}
	~MapJson() {
		std::fstream file; file.open(Name, std::ios::out | std::ios::trunc);
		std::string temp = object.dump(2);
		file << temp;
		file.close();
	}
};
//DebugFunction()
void CreateMap() {
	Maps TestMap;
	int sizex, sizey;
	GetValue(sizex, "¬ведите размер грового пол€ (строки) > ");
	GetValue(sizey, "¬ведите размер грового пол€ (столбци) > ");
	GetValue(TestMap.player, "¬ведите знак персонажа > ");
	GetValue(TestMap.enemy, "¬ведите знак врага > ");
	GetValue(TestMap.wall, "¬ведите знак стены > ");
	GetValue(TestMap.point, "¬ведите знак монеты > ");
	GetValue(TestMap.injection1, "¬ведите знак угла1 > ");
	GetValue(TestMap.injection2, "¬ведите знак угла2 > ");
	GetValue(TestMap.injection3, "¬ведите знак угла3 > ");
	GetValue(TestMap.injection4, "¬ведите знак угла4 > ");
	TestMap.CurMap.resize(sizex);
	for (int i = 0; i < TestMap.CurMap.size(); i++) {
		for (int j = 0; j < sizey; j++) {
			TestMap.CurMap[i] += ' ';
		}
	}
	system("CLS");
	hidecursor();
	for (int i = 0; i < TestMap.CurMap.size(); i++) {
		for (int j = 0; j < TestMap.CurMap[i].length(); j++) {
			if (i == 0 && j == 0)WordColor(TestMap.CurMap[i][j], White, Black);
			else WordColor(TestMap.CurMap[i][j], DarkGray, LightGray);
		}
		std::cout << std::endl;
	}
	for (int i = 4; i < TestMap.GetDesignations().size(); ++i) {
		if (i == 4)WordColor(TestMap.GetDesignations()[i], White, Green);
		else WordColor(TestMap.GetDesignations()[i], DarkGray, Red);
	}
	for (int curi = 0, curj = 0, curx = 0;;) {
		switch (_getch()) {
		case Key_Up:
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], DarkGray, LightGray);
			curi--;
			if (curi < 0)curi = TestMap.CurMap.size() - 1;
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], White, Black);
			break;
		case Key_Down:
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], DarkGray, LightGray);
			curi++;
			if (curi >= TestMap.CurMap.size())curi = 0;
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], White, Black);
			break;
		case Key_Left:
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], DarkGray, LightGray);
			curj--;
			if (curj < 0)curj = TestMap.CurMap[curi].size() - 1;
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], White, Black);
			break;
		case Key_Right:
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], DarkGray, LightGray);
			curj++;
			if (curj >= TestMap.CurMap[curi].size())curj = 0;
			setCursorPosition(curi, curj); WordColor(TestMap.CurMap[curi][curj], White, Black);
			break;
		case Key_Plus:
			setCursorPosition(TestMap.CurMap[curi].size(), curx); WordColor(TestMap.GetDesignations()[curx], DarkGray, Red);
			curx++;
			if (curx >= TestMap.GetDesignations().size())curx = 4;
			setCursorPosition(TestMap.CurMap[curi].size(), curx); WordColor(TestMap.GetDesignations()[curx], White, Green);
			break;
		case Key_Minus:
			setCursorPosition(TestMap.CurMap[curi].size(), curx); WordColor(TestMap.GetDesignations()[curx], DarkGray, Red);
			curx--;
			if (curx < 4)curx = TestMap.GetDesignations().size() - 1;
			setCursorPosition(TestMap.CurMap[curi].size(), curx); WordColor(TestMap.GetDesignations()[curx], White, Green);
			break;
		case Key_Enter:
			if (curx == 5) {
				for (int i = 0; i < TestMap.CurMap[curi].size(); ++i) {
					for (int j = 0; j < TestMap.CurMap[i].length(); j++) {
						if (TestMap.CurMap[i][j] == TestMap.GetDesignations()[5]) {
							TestMap.CurMap[i][j] = ' ';
							setCursorPosition(i, j); WordColor(' ', DarkGray, LightGray);
							break;
						}
					}
				}
			}
			TestMap.CurMap[curi][curj] = TestMap.GetDesignations()[curx];
			setCursorPosition(curi, curj); WordColor(TestMap.GetDesignations()[curx], DarkGray, LightGray);
			break;
		case Key_q:
			MapJson obj;
			system("CLS");
			obj.AddNewMap(GetValue("¬ведите им€ карты > "), TestMap);
			return;
			break;
		}

	}

}


