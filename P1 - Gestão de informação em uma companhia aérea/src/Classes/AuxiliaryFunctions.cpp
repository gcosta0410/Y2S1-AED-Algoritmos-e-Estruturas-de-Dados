#include <iostream>
#include "AuxiliaryFunctions.h"
#include <algorithm>
#include <ctime>

/**
 * Returns today's date
 * @return
 */
Date getDateNow() {
    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);

    unsigned int day = aTime->tm_mday;
    unsigned int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    unsigned int year = aTime->tm_year + 1900; // Year is # years since 1900
    return {year,month,day};
}

/**
 * Finds a flight in a list searching by flight number
 * @param l
 * @param number
 * @return
 */
Flight * findInList(const list<Flight*>& l, int number) {
    for(auto el: l){
        if (el->getNumber() == number) return el;
    }
    return new Flight(new Airport(), new Airport());
}

/**
 * Returns the time now
 * @return
 */
Time_m getTimeNow() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    return {now->tm_hour, now->tm_min};
}

/**
 * Checks if appears later than today's date
 * @param d
 * @return
 */
bool checkDate(Date d){
    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);

    int day = aTime->tm_mday;
    int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime->tm_year + 1900; // Year is # years since 1900
    Date dNow(year,month,day);

    return  dNow < d;
}

/**
 * Checks if a plane has a flight on that date
 * @param d1
 * @param plane
 * @return true if the plane is available
 */
bool checkForPlaneAvailability(Date d1, const Plane& plane){
    std::list<Flight*> flights = plane.getFlights();
    for(auto idx = flights.begin(); idx != flights.end(); idx++){
        if((*idx)->getDateDeparture() == d1) return false;
    }
    return true;
}

/**
 * Order by bigger capacity first, then by alphabetic order of the registration plate
 * @param p1
 * @param p2
 * @return
 */
bool comparePlanesByCapacity(const Plane& p1, const Plane& p2){
    if(p1.getCapacity() == p2.getCapacity()) return p1.getRegistrationPlate() < p2.getRegistrationPlate();
    return (p1.getCapacity() > p2.getCapacity());
}

/**
 * Order by alphabetic order of the registration plate, then by bigger capacity
 * @param p1
 * @param p2
 * @return
 */
bool comparePlanesByPlate(const Plane& p1, const Plane& p2){
    if(p1.getCapacity() == p2.getCapacity()) return p1.getCapacity() > p2.getCapacity();
    return (p1.getRegistrationPlate() < p2.getRegistrationPlate());
}

/**
 * Order by alphabetic order of the aircraft type, then by bigger capacity
 * @param p1
 * @param p2
 * @return
 */
bool comparePlanesByType(const Plane& p1, const Plane& p2){
    if(p1.getCapacity() == p2.getCapacity()) return p1.getCapacity() > p2.getCapacity();
    return (p1.getPlaneType() < p2.getPlaneType());
}

/**
 * Get a yes ('Y') or no ('N') answer
 * @return true if Yes, false if No
 */
bool getAnswer() {
    char answer;
    answer = toupper(getChar());
    while (!(('Y' == answer) || ('N' == answer))) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid answer! Enter again: ";
        answer = toupper(getChar());
    }
    return (answer == 'Y');
}


/**
 * Checks if a string represents a number
 * @param str
 * @return
 */
bool isAllDigits(const std::string &str){

    // Iterates each character in a std::string and checks if it's an integer or not
    if(str.empty()) return false;
    for(char c: str){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

/**
 * Checks if a string represents a number in more compact way
 * @param s
 * @return
 */
bool isNumber(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

/**
 * Check if a number in the correct interval (0 to a) is inputted
 * @param a
 * @param text
 * @return
 */
bool parseInput(int a, const string& text){
    vector<int> values;
    for(int i = 0; i <= a; i++){
        values.push_back(i);
    }
    auto it = values.begin();
    if (isAllDigits(text)) {
        it = std::find(values.begin(), values.end(), stoi(text));
        if (it != values.end()) {
            return true;
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    } else {
        std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
    }
    return false;
}


bool compareTimes(const Time_m &t1, const Time_m &t2) {
    return t1 < t2;
}

/**
 * Checks if a time is between two others
 * @param time
 * @param left
 * @param right
 * @return
 */
bool timeIsBetween(Time_m time, Time_m left, Time_m right) {
    return time-left < right-left; //e.g. 23:00 is between 22:00 and 01:00, 15:00 is betweem 01:00 and 22:00
}

/**
 * Checks if the time string represents a valid time
 * @param time_str
 * @return
 */
bool validateTime(std::string time_str) {
    if (time_str.length() != 5 || time_str[2] != ':' || !isNumber(time_str.substr(0, 2)) ||
        !isNumber(time_str.substr(3, 5))) {
        std::cerr << "Invalid time string. Expected format [HH:MM]" << std::endl;
        return false;
    }
    else {
        int hours = stoi(time_str.substr(0, 2));
        int minutes = stoi(time_str.substr(3, 2));
        if (hours > 23 || hours < 0 || minutes > 59 || minutes < 0) {
            std::cerr << "Invalid time. 0 <= HH <= 23 and 0 <= MM <= 59" << std::endl;
            return false;
        }
        return true;
    }
}

char getChar() {
    char letter;
    std::cin >> letter;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input! Enter again: ";
        std::cin >> letter;
    }
    return letter;
}

float getFloat() {
    float aux;
    std::cin >> aux;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Enter again: ";
        std::cin >> aux;
    }
    std::cin.ignore(10000, '\n');
    return aux;
}

int getInt() {
    int aux;
    std::cin >> aux;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Enter again: ";
        std::cin >> aux;
    }
    std::cin.ignore(10000, '\n');
    return aux;
}

/**
 * Converts the position in a matrix to the its corresponding element number
 * @param number
 * @param i
 * @param j
 * @param cols
 * @return
 */
int ijToSeat(int number, int i, int j, int cols) {
    return i * cols + j + 1;
}

/**
 * Show the 3 (at most) closest schedules to the time now
 * @param out
 * @param schedule
 * @return
 */
std::ostream &showSchedule(ostream &out, const vector<Time_m> &schedule) {
    Time_m now = getTimeNow();
    auto s = schedule.size();
    if (s == 1) out << "Departure: " << schedule[0] << std::endl;
    else if (s == 2)
        out << "Departure: " << schedule[0] << std::endl << "Departure: " << schedule[1] << std::endl;
    else {
        for (int i = 0; i < s; i++) {
            if (timeIsBetween(now, schedule[i], schedule[(i + 1) % s])) {
                out << "Departure: " << schedule[(i + 1) % s] << std::endl
                    << "Departure: " << schedule[(i + 2) % s] << std::endl
                    << "Departure: " << schedule[(i + 3) % s] << std::endl;
                break;
            }
        }
    }
    return out;
}

/**
 * Returns the position in a matrix given the numeration of the element
 * @param number
 * @param cols
 * @return
 */
std::pair<unsigned int,unsigned int> seatToij(unsigned int number,unsigned int cols) {
    std::pair<unsigned int,unsigned  int> res;
    res.second = (number - 1) % cols;
    res.first = (number - res.second - 1) / cols;
    return res;
}

std::string getName() {
    std::string name;
    std::cin.ignore();
    getline(std::cin,name);
    return name;
}

std::string getString() {
    std::string name;
    std::cin >> name;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Enter again: ";
        std::cin >> name;
    }
    std::cin.ignore(10000, '\n');
    return name;
}

/**
 * Returns a string in lowercase
 * @param original
 * @return
 */
std::string toLowerStr(std::string original) {
    std::string lower = original;
    for (char & i : lower)
        i = tolower(i);
    return lower;
}

/**
 * Creates a schedule for a transport given its first and last occurrences and the frequency of trips
 * @param start_time
 * @param end_time
 * @param frequency
 * @return
 */
std::vector<Time_m> createSchedule(Time_m start_time, Time_m end_time, Time_m frequency) {
    std::vector<Time_m> res;
    while(start_time <= end_time){
        res.push_back(start_time);
        start_time = start_time + frequency;
    }
    return res;
}

unsigned int getUnsignedInt() {
    unsigned int aux;
    std::cin >> aux;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Enter again: ";
        std::cin >> aux;
    }
    std::cin.ignore(10000, '\n');
    return aux;
}

void clrscr() {
    std::cout << std::string(100,'\n');
}