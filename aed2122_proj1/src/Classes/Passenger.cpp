#include "Passenger.h"


int Passenger::current_id = 1000; //Person ID starts at 1000
Passenger::Passenger(const std::string& name) : Person(name) {
    this->name = name;
    this->passenger_id = ++current_id;
}

/**
 * The passenger gets a ticket for a certain flight
 * @param ticket
 */
void Passenger::giveTicket(Ticket *new_ticket) {
    this->ticket = new_ticket;
}

int Passenger::getId() const {
    return passenger_id;
}
