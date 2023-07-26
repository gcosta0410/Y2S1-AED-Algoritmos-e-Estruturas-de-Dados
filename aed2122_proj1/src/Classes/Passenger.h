#ifndef AED2122_PASSENGER_H
#define AED2122_PASSENGER_H

#include "Person.h"
#include "Ticket.h"

class Passenger: public Person {
private:
    Ticket* ticket{};
    int passenger_id;
public:
    static int current_id;
    explicit Passenger(const std::string& name);
    void giveTicket(Ticket* ticket);
    int getId() const;
};


#endif //AED2122_PASSENGER_H
