#include "Seat.h"
/**
 * Creates a seat, unoccupied by default
 * @param number
 */
Seat::Seat(unsigned int number) {
    this->number = number;
    this->is_taken = false;
    this->symbol =  std::to_string(this->number);
}
/**
 * Occupies the seat
 */
void Seat::take() {
    this->is_taken = true;
    this->symbol = SEAT_TAKEN;
}

std::string Seat::getSymbol() const {
    return symbol;
}
/**
 * Checks whether the seat is still available/not taken
 * @return
 */
bool Seat::isAvailable() const {
    return !is_taken;
}
