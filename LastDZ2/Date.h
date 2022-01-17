#pragma once
#include<iostream>
namespace Dates {
	class Date {
	public:
		static std::string getStringDate(time_t x) {
			struct tm* timeinfo;
			timeinfo = localtime(&x);
			return static_cast<std::string>(asctime(timeinfo));
		}
	};
}