#include "Time_m.h"
#include "AuxiliaryFunctions.h"

/**
 * Constructs a Time_m object given the hours and minutes components
 * @param hours
 * @param mins
 */
Time_m::Time_m(int hours, int mins) {

    //Warns if the time is invalid
    if (hours >= 60 || mins >= 60 || hours < 0 || minutes < 0) {
        std::cerr << "Invalid Time (Time_m constructor)" << std::endl;
    }
    this->hours = hours;
    this->minutes = mins;
}

Time_m::Time_m() {
    hours = 0;
    minutes = 0;
}

/**
 * Adds two time
 * @param time_to_add
 * @return
 */
Time_m Time_m::operator+ (const Time_m& time_to_add) const {
    int nTotalMinutes(minutes + time_to_add.getMinutes());
    int nMinutes(nTotalMinutes % 60);
    int nHours(nTotalMinutes/60 + (hours + time_to_add.getHours()));

    return {nHours, nMinutes};
}

/**
 * Constructs a time given a string in the format HH:MM.
 * The string should already be in the correct format and represent a valid time.
 * @param str
 */
Time_m::Time_m(const std::string& str) {
   hours  = stoi(str.substr(0, 2));
    minutes = stoi(str.substr(3, 2));
}

/**
 *
 * @param rTime
 * @return
 */
Time_m Time_m::operator - (const Time_m& time_to_subtract) const {
    // Get the difference in seconds
    int nDiff(hours * 3600 + minutes * 60 - (time_to_subtract.getHours() * 3600 + time_to_subtract.getMinutes() * 60));
    if (nDiff < 0) nDiff += (3600 * 24);
    int nHours(nDiff/3600);
    int nMins((nDiff%3600)/60);

    return {nHours, nMins};
}

/**
 * Get the time in "HH:MM" format
 * @return
 */
std::string Time_m::timeStr() const {
    //Fill with a leading 0 if HH/MM are in single digits
    return ((hours < 10) ? std::string("0") + std::to_string(hours) : std::to_string(hours))
           + std::string(":")
           + ((minutes < 10) ? std::string("0") + std::to_string(minutes) : std::to_string(minutes));
}

/**
 * Verifies if one time is less than the other, minimum is 00:00 and maximum is 23:59
 * @param t2
 * @return
 */
bool Time_m::operator<(const Time_m &t2) const {
    if (hours < t2.hours) return true;
    else if(hours == t2.hours) return minutes < t2.minutes;
    return false;
}

/**
 * Verifies if one time is the same or less than the other, minimum is 00:00 and maximum is 23:59
 * @param t2
 * @return
 */
bool Time_m::operator<=(const Time_m &t2) const {
    if (hours < t2.hours) return true;
    else if (hours == t2.hours) return minutes <= t2.minutes;
    return false;
}

/**
 * Print or put in a stream the time in "HH:MM" format
 * @param out
 * @param time
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Time_m& time) {
    std::string res = ((time.hours < 10) ? std::string("0") + std::to_string(time.hours) : std::to_string(time.hours))
    + std::string(":")+ ((time.minutes < 10) ? std::string("0") + std::to_string(time.minutes) : std::to_string(time.minutes));
    out << res;
    return out;

}
/**
 * Checks if two times are the same
 * @param t2
 * @return
 */
bool Time_m::operator==(const Time_m &t2) const {
    return hours == t2. hours && minutes == t2. minutes;
}

/**
 * Validates an already created object of Time_m
 * @return
 */
bool Time_m::validTime() const {
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return false;
    return true;
}

/**
 * Checks if string represents a valid time ocnvertable to a Time_m object
 * @param time_str
 * @return
 */
bool Time_m::validTimeStr(const std::string& time_str) {
    if (time_str.length() != 5 || time_str[2] != ':' || !isNumber(time_str.substr(0, 2)) ||
        !isNumber(time_str.substr(3, 5))) {
        return false;
    } else {
        int nhours = stoi(time_str.substr(0, 2));
        int nminutes = stoi(time_str.substr(3, 2));
        if (nhours > 23 || nhours < 0 || nminutes > 59 || nminutes < 0) {
            return false;

        }
        return true;

    }
}