#include <iostream>
#include "time.h"
#include <iomanip>

Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) {
    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

Time::Time(const Time& aTime) {
    hour = aTime.getHour();
    minute = aTime.getMinute();
    second = aTime.getSecond();
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::setHour(int aHour) {
    hour = aHour;
}

void Time::setMinute(int aMinute) {
    minute = aMinute;
}

void Time::setSecond(int aSecond) {
    second = aSecond;
}

void Time::PrintAMPM() const {
    
    if (hour > 12) { 
        //PM Print
        std::cout << std::setw(2) << std::setfill('0') << (hour - 12) << ':' 
                  << std::setw(2) << std::setfill('0') << minute << ':' 
                  << std::setw(2) << std::setfill('0') << second << " PM" << std::endl;
    }
    else if (hour == 12) {
        std::cout << std::setw(2) << std::setfill('0') << hour << ':'
                  << std::setw(2) << std::setfill('0') << minute << ':'
                  << std::setw(2) << std::setfill('0') << second << " PM" << std::endl;

    }
    else {
        std::cout << std::setw(2) << std::setfill('0') << hour << ':'
                  << std::setw(2) << std::setfill('0') << minute << ':'
                  << std::setw(2) << std::setfill('0') << second << " AM" << std::endl;
    }
}

bool IsEarlierThan(const Time& time1, const Time& time2) {
    //Compare Hours
    if(time1.getHour() < time2.getHour()) {
        return true;
    }
    else if (time1.getHour() > time2.getHour()) {
        return false;
    }
    //Compare Minutes
    if (time1.getMinute() < time2.getMinute()) {
        return true;
    }
    else if (time1.getMinute() > time2.getMinute()) {
        return false;
    }
    //Compare Seconds
    if (time1.getSecond() < time2.getSecond()) {
        return true;
    }
    else if (time1.getSecond() > time2.getSecond()) {
        return false;
    }
    return false;
}