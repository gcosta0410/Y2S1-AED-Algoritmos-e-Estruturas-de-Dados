#include "Ticket.h"

/**
 * Constructs a ticket relative to a flight, owned by a passenger that will fly in a certain seat and carry luggage
 * @param flight_id
 * @param seat_number
 * @param passenger_id
 * @param passenger_name
 * @param luggage
 */
Ticket::Ticket(unsigned int flight_id, unsigned int seat_number,unsigned int passenger_id, std::string passenger_name,Luggage luggage) {
    this->flight_id = flight_id;
    this->seat_number = seat_number;
    this->luggage = luggage;
    this->passenger_id = passenger_id;
    this->passenger_name = passenger_name;
}

void Ticket::setFlightId(unsigned int id) {
    flight_id = id;
}


void Ticket::setLuggage(const Luggage& lugg) {
    this->luggage = lugg;
}

unsigned int Ticket::getFlightId() const {
    return flight_id;
}

unsigned int Ticket::getPassengerId() const {
    return passenger_id;
}

unsigned int Ticket::getSeat() const {
    return seat_number;
}

std::string Ticket::getPassengerName() {
    return passenger_name;
}

/**
 * Checks if the owner has any luggage
 * @return
 */
bool Ticket::luggageNotEmpty() {
    return luggage.notEmpty();
}

/**
 * Weight of the luggage of the owner
 * @return
 */
unsigned int Ticket::luggageWeight() {
    return luggage.getWeight();
}

/**
 * Checks whether the owner chose to automatically check-in their luggage
 * @return
 */
bool Ticket::luggageIsInCar() const {
    return luggage.getIsInCar();
}
