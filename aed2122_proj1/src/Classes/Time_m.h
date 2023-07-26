#ifndef AED2122_TIME_M_H
#define AED2122_TIME_M_H


#include <string>
#include <iostream>


class Time_m {
private:
    int hours;
    int minutes;
public:
    Time_m(int hours, int mins);
    Time_m();
    Time_m(const std::string& str);
    Time_m operator+ (const Time_m& time_to_add) const;
    Time_m operator - (const Time_m& time_to_subtract) const;
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    std::string timeStr() const;
    friend std::ostream& operator<<(std::ostream& out, const Time_m& time);
    bool operator <(const Time_m& t2) const;
    bool operator <=(const Time_m& t2) const;
    bool operator ==(const Time_m& t2) const;
    bool validTime() const;
    static bool validTimeStr(const std::string& time_str);
};

#endif //AED2122_TIME_M_H
