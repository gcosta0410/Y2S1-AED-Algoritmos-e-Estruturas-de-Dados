#ifndef AED2122_DATE_H
#define AED2122_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date{

private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
    static inline bool LeapYear(unsigned int year);
    static const int MaxDayInMonth[13]; // Holds all max days in a general year
public:
    Date(unsigned int year, unsigned int month, unsigned int day):year(year), month(month), day(day) {}
    Date():year(0), month(0), day(0){}

    Date operator + (unsigned int days) const;
    bool operator <(const Date&d1) const;
    bool operator <=(const Date&d1) const;
    bool operator ==(const Date &d1) const;
    unsigned int getYear() const  { return year; }
    unsigned int getMonth() const { return month; }
    unsigned int getDay() const   { return day; }
    string dateStr() const;
    string dateStrLoad() const;

};

#endif //AED2122_DATE_H
