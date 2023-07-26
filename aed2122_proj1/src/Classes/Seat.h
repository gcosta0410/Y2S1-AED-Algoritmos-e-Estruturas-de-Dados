#ifndef AED2122_SEAT_H
#define AED2122_SEAT_H

#include <string>
#define SEAT_TAKEN "X"
class Seat {
private:
    unsigned int number;
    bool is_taken; //Whether the seat is occupied
    std::string symbol; //The symbol of the seat to print: its number or SEAT_TAKEN
public:
    Seat(unsigned int number);
    bool isAvailable() const;
    void take();
    std::string getSymbol() const;

};


#endif //AED2122_SEAT_H
