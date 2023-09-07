#ifndef __date_h_
#define __date_h_

// File: date.h
// Purpose: Header file with declaration of the Date class, including
// member functions and private member variables.
class Date {
public:
	// CONSTRUCTORS
	Date(int aMonth, int aDay, int aYear);
	// ACCESSORS
	int getDay() const { return day; };
	int getMonth() const { return month; };
	int getYear() const { return year; };
	// MODIFIERS
	void setDay(int aDay) { day = aDay; };
	void setMonth(int aMonth) { month = aMonth; };
	void setYear(int aYear) { year = aYear; };
	// other member functions that operate on date objects
	bool isEqual(const Date& date2) const; // same day, month, & year?
	void print() const; // output as month/day/year

private: // REPRESENTATION (member variables)
	int month;
	int day;
	int year;
};

//Operator <
bool operator< (const Date& left,const Date& right);

//Operator >
//bool operator> (const Date& left, const Date& right);

int StringToMonth(std::string monthName);

std::string MonthToString(int month);

std::ostream& operator<< (std::ostream& ostr, const Date& d);
#endif