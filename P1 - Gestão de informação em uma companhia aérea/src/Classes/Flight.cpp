#include <iomanip>
#include "Flight.h"
#include "AuxiliaryFunctions.h"

/**
 * Create flight given the airports
 * @param origin
 * @param destination
 * @param max_occupation
 * @param cols
 * @param departure
 * @param time
 * @param duration
 * @param occupation
 * @param passengers
 * @param car_c
 * @param car_n
 * @param car_m
 */
Flight::Flight(Airport *origin, Airport *destination, unsigned int max_occupation, unsigned int cols,
               Date departure, Time_m time, unsigned int duration,
               unsigned int occupation, const vector<Passenger>& passengers, unsigned int car_c,
               unsigned int car_n, unsigned int car_m){
    this->DateDeparture = departure; this->destination = destination;
    this->origin = origin;  this->max_occupation = max_occupation;
    this->current_occupation = occupation; this-> cols = cols; this->duration = duration;
    this->time = time;

    this->rows = max_occupation / cols;
    for(int i = 0; i < rows; i++){
        std::vector<Seat> aux;
        for(int j = 0; j < cols; j++){
            Seat seat = Seat(i * cols + j + 1);
            aux.push_back(seat);
        }
        seats.push_back(aux);
    }
    number = flight_counter;
    transport_car = TransportCar(car_c,car_n,car_m);
}

unsigned Flight::flight_counter = 1; //Start the flight id at 1

Airport * Flight::getOrigin() const {
    return origin;
}
Airport * Flight::getDestination() const {
    return destination;
}
std::string Flight::getPlanePlate() const {
    return this->plane_registration_plate;
}
/**
 * Get the departure time converted to a string of the format "HH:MM"
 * @return
 */
std::string Flight::getTimeStr() const {
    return time.timeStr();
}
std::vector<Passenger> *Flight::getPassengers(){
    return &passengers;
}
Date Flight::getDateDeparture() const {
    return DateDeparture;
}
CarDimensions Flight::getCarDimensions() const {
    return CarDimensions{transport_car.getC(), transport_car.getN(), transport_car.getM()};
}
unsigned int Flight::getCols() const {
    return this->cols;
}
unsigned int Flight::getNumber() const {
    return this->number;
}

void Flight::setDuration(unsigned int new_duration) {
    this->duration = new_duration;

}

void Flight::setOrigin(Airport *new_origin) {
    this->origin = new_origin;
}

void Flight::setDestination(Airport *new_destination) {
    this->destination = new_destination;
}

void Flight::setPlanePlate(string plate) {
    this->plane_registration_plate = plate;

}
void Flight::setTime(Time_m t) {
    time = t;
}
void Flight::setDate(Date date) {
    this->DateDeparture = date;
}
void Flight::setMaxOccupation(unsigned int max) {
    max_occupation = max;
    current_occupation = 0;
}
void Flight::setCols(unsigned int new_cols) {
    this->cols = new_cols;
    this->rows = max_occupation / cols;
}
/**
 * Checks if the flight can accommodate more passengers
 * @param number_of_passengers
 * @return
 */
bool Flight::notFull(unsigned number_of_passengers) const {
    return current_occupation + number_of_passengers <= max_occupation;
}

/**
 * Print the seats of the flight as a number or SEAT_TAKEN symbol according to the plane configuration of the seats
 */
void Flight::showSeats() const {
    std::cout << endl;
    for(int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(j == cols / 2) {
                std::cout << "\t";
            }
            std::cout << setw(4)<<seats[i][j].getSymbol()<< " " ;
        }
        std::cout << endl;
    }
}

/**
 * Prints flight information useful for an admin
 */
void Flight::showFlight() const {
    std::cout <<"Flight no. " <<  number << " will take place in the plane with the plate " << plane_registration_plate << ";" << std::endl;
    std::cout << "Departs on " << DateDeparture.dateStr() << " at " << time <<" and has a duration of " << duration << " hours;" << std::endl;
    std::cout << "Has an occupation of " << current_occupation << "/" << max_occupation << " seats;" << std::endl;
    std::cout << "It will depart from " << origin->getName() << " in "<< origin->getCity() << " and arrive at " << destination->getName() << " in "<< destination->getCity() << "." << std::endl;
}

/**
 * Prints flight info useful for a passenger
 */
void Flight::showFlightToPassenger() const {
    std::cout <<"Flight no. " <<  number << ";" << std::endl;
    std::cout << "Departs on " << DateDeparture.dateStr() <<", " << time << " and has a duration of " << duration << " hours;"<< std::endl;
    std::cout << "Has an occupation of " << current_occupation << "/" << max_occupation << " seats;" << std::endl;
    std::cout << "It will depart from " << origin->getName() << " in "<< origin->getCity() << " and arrive at " << destination->getName() << " in "<< destination->getCity() << "." << std::endl;
}

/**
 * Shows the transport car's current occupation
 */
void Flight::showCar() const {
    transport_car.showCar();
}


/**
 * Reserves a seat if it is still free and returns the success of the operation
 * @param seat_number
 * @return true if the seat is available
 */
bool Flight::validSeat(unsigned int seat_number) {
    unsigned int i = seatToij(seat_number, cols).first;
    unsigned int j = seatToij(seat_number, cols).second;
    if (seat_number <= 0 || seat_number > max_occupation) return false;
    if (seats[i][j].isAvailable()) {
        seats[i][j].take();
        return true;
    }
    else return false;
}
/**
 * Adds a passenger to the flight, reducing the number of free seats
 * @param passenger
 */
void Flight::addPassenger(const Passenger &passenger) {
    passengers.push_back(passenger);
    current_occupation++;
}
/**
 * Checks the equality of two flights only by airport names. Used to check if a matching flight was not found
 * @param f flight to be compared
 * @return
 */
bool Flight::operator==(const Flight &f) const {
    return origin->getName() == f.getOrigin()->getName() && destination->getName() == f.getDestination()->getName();
}

/**
 * Creates seats to match the plane configuration, all are empty by default
 */
void Flight::configureSeats() {
    this->rows = max_occupation / cols;
    for(int i = 0; i < rows; i++){
        std::vector<Seat> aux;
        for(int j = 0; j < cols; j++){
            Seat seat = Seat(i * cols + j + 1);
            aux.push_back(seat);
        }
        seats.push_back(aux);
    }
}

/**
 * Add a luggage to the conveyor if possible
 * @param lug
 * @return true if there was enough space in the transport car
 */
bool Flight::addToConveyor(const Luggage& lug) {
    return transport_car.addToConveyor(lug);
}
/**
 * Moves luggage from the conveyor to transport car one at a time
 */
void Flight::loadToCar() {
   transport_car.loadToCar();
}

void Flight::incrementFlightCounter() {
    flight_counter++;

}


