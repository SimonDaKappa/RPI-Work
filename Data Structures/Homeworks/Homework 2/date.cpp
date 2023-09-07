#include <iostream>
#include "date.h"

Date::Date(
			int aMonth,
			int aDay,
			int aYear) 
			:
			month(aMonth),
			day(aDay),
			year(aYear)
			{}

bool Date::isEqual(const Date& date2) const {
	return day == date2.day && month == date2.month && year == date2.year;
}

void Date::print() const {
	std::cout << month << "/" << day << "/" << year;
}

bool sameDay(const Date& date1, const Date& date2) {
	return date1.getDay() == date2.getDay() && date1.getMonth() == date2.getMonth();
}

int StringToMonth(std::string monthName) {
	//Helper Function to conver parsed int into
	//its month name counterpart
	if (monthName == "January") return 1;
	if (monthName == "February") return 2;
	if (monthName == "March") return 3;
	if (monthName == "April") return 4;
	if (monthName == "May") return 5;
	if (monthName == "June") return 6;
	if (monthName == "July") return 7;
	if (monthName == "August") return 8;
	if (monthName == "September") return 9;
	if (monthName == "October") return 10;
	if (monthName == "November") return 11;
	if (monthName == "December") return 12;
	
	//error checking
	std::cerr << "Invalid Month Name in File Format\n";
	exit(0);
}

std::string MonthToString(int month) {
	//Helper Function to convert a parsed month name into
	//its int counterpart
	switch (month) {
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4: 
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	}

	//error checking
	std::cerr << "Invalid Month Name in File Format\n";
	exit(0);
}

bool operator< (const Date& left,const Date& right) {
	if (left.getYear() < right.getYear()) 
		return true;
	else if (left.getYear() == right.getYear()) {
		if (left.getMonth() < right.getMonth()) {
			return true;
		}
		else if (left.getMonth() == right.getMonth()) {
			if (left.getDay() < right.getDay()) {
				return true;
			}
		}
	}
	return false; //equal || greater day -> false
}

std::ostream& operator<< (std::ostream& ostr, const Date& d) {
	ostr << d.getMonth() << '/' << d.getDay() << '/' << d.getYear();
	return ostr;
}