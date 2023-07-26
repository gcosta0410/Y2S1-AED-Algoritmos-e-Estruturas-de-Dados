#ifndef AED2122_AUXILIARYFUNCTIONS_H
#define AED2122_AUXILIARYFUNCTIONS_H

#include <iostream>
#include <list>
#include "Flight.h"
#include "Plane.h"
#include <algorithm>


Date getDateNow();
Flight * findInList(const std::list<Flight*>& l, int number);
Time_m getTimeNow();
bool checkDate(Date d);
bool checkForPlaneAvailability(Date d1, const Plane& plane);
bool comparePlanesByCapacity(const Plane& p1, const Plane& p2);
bool comparePlanesByPlate(const Plane& p1, const Plane& p2);
bool comparePlanesByType(const Plane& p1, const Plane& p2);
bool getAnswer();
bool isAllDigits(const std::string &str);
bool isNumber(const std::string &s);
bool parseInput(int a, const string& text);
bool compareTimes(const Time_m &t1, const Time_m &t2);
bool timeIsBetween(Time_m time, Time_m left, Time_m right);
bool validateTime(std::string time_str);
char getChar();
float getFloat();
int getInt();
int ijToSeat(int number,int i, int j, int cols);
std::ostream& showSchedule(std::ostream& out, const vector<Time_m> &schedule );
std::pair<unsigned int,unsigned int> seatToij(unsigned int number,unsigned  int cols);
std::string getName();
std::string getString();
std::string toLowerStr(std::string original);
std::vector<Time_m> createSchedule(Time_m start_time, Time_m end_time, Time_m frequency);
unsigned int getUnsignedInt();
void clrscr();

#endif //AED2122_AUXILIARYFUNCTIONS_H
