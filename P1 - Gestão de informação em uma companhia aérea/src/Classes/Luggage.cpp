#include "Luggage.h"

Luggage::Luggage(unsigned int id, unsigned int weight, bool in_car) {
    this->owner_id = id;
    this->weight = weight;
    this->in_car = in_car;
}

void Luggage::setId(int id) {
    this->owner_id = id;
}

Luggage::Luggage() {
    this->owner_id = 0;
    this->weight = 0;
    this->in_car = false;
}
/**
 * The luggage is not empty if its weight is positive
 * @return
 */
bool Luggage::notEmpty() const {
    return weight > 0;
}

unsigned int Luggage::getWeight() const {
    return weight;
}

bool Luggage::getIsInCar() const {
    return in_car;
}

