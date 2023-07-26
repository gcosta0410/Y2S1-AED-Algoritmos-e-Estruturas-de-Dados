#ifndef AED2122_TICKET_H
#define AED2122_TICKET_H

#include "Luggage.h"

class Ticket {
public:
    Ticket(unsigned flight_id, unsigned int seat_number,unsigned int passenger_id,std::string passenger_name, Luggage luggage);
    unsigned int getFlightId() const;
    unsigned int getPassengerId() const;
    unsigned int getSeat() const;
    void setFlightId(unsigned int id);
    void setLuggage(const Luggage& luggage);
    bool luggageNotEmpty();
    bool luggageIsInCar() const;
    unsigned int luggageWeight();
    std::string getPassengerName();

private:
    unsigned int flight_id;
    unsigned int passenger_id;
    std::string passenger_name;
    unsigned int seat_number;
    Luggage luggage;
};

#endif //AED2122_TICKET_H
