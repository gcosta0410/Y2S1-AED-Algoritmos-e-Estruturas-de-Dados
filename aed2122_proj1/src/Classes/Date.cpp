#include "Date.h"

// Define MaxDayInMonth
const int Date::MaxDayInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * Add specified number of days to the Date
 * @param days
 * @return
 */
Date Date::operator + (unsigned int days) const {
    // Maximum days in the month
    unsigned int nMaxDays(MaxDayInMonth[month] + (month == 2 && LeapYear(year) ? 1 : 0));

    // Initialize the Year, Month, Days
    unsigned int nYear(year);
    unsigned int nMonth(month);
    unsigned int nDays(day + days);

    // Iterate till it becomes a valid day of a month
    while (nDays > nMaxDays) {
        // Subtract the max number of days of current month
        nDays -= nMaxDays;

        // Advance to next month
        ++nMonth;

        // Falls on to next year?
        if (nMonth > 12) {
            nMonth = 1; // January
            ++nYear;    // Next year
        }

        // Update the max days of the new month
        nMaxDays = MaxDayInMonth[nMonth] + (nMonth == 2 && LeapYear(nYear) ? 1 : 0);
    }

    return {nYear, nMonth, nDays};
}

bool Date::operator ==(const Date &d1) const{
    if(month == d1.month && day == d1.day && year == d1.year) return true;
    else return false;
}


/// Get the Date string in yyyy/mm/dd format
string Date::dateStr() const {
    return to_string(year)
           + string("/")
           + string(month < 10 ? string("0") + to_string(month) : to_string(month))
           + string("/")
           + string(day < 10 ? string("0") + to_string(day) : to_string(day));
}

bool Date::operator<(const Date &d1) const {
    if(year != d1.year){
        return year < d1.year;
    }
    else if(month != d1.month){
        return month < d1.month;
    }
    else return day < d1.day;
}

bool Date::operator<=(const Date &d1) const {
    if(year != d1.year){
        return year < d1.year;
    }
    else if(month != d1.month){
        return month < d1.month;
    }
    else return day <= d1.day;
}
/**
 * Same as dateStr but uses separator ',' to be file friendly
 * @return
 */
string Date::dateStrLoad() const {
        return to_string(year)
               + string(",")
               + string(month < 10 ? string("0") + to_string(month) : to_string(month))
               + string(",")
               + string(day < 10 ? string("0") + to_string(day) : to_string(day));
}
/**
 * Leap year check
 * @param year
 * @return
 */
bool Date::LeapYear(unsigned int year) {
     return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}


