#include "Plane.h"
/**
 * Creates a plane
 * @param registration_plate
 * @param plane_type
 * @param max_capacity
 * @param n_cols
 */
Plane::Plane(std::string registration_plate, std::string plane_type, unsigned int max_capacity, unsigned int n_cols) {
    this->registration_plate = registration_plate;
    this->plane_type = plane_type;
    this->capacity = max_capacity;
    this->cols = n_cols;
    this->rows = this->capacity / this->cols;
}

std::string Plane::getRegistrationPlate() const {
    return this->registration_plate;
}

std::string Plane::getPlaneType() const {
    return this->plane_type;
}

unsigned int Plane::getCapacity() const {
    return this->capacity;
}

unsigned int Plane::getCols() const {
    return this->cols;
}

/**
 * Adds a flight to the flight_plan, configuring it
 * @param flight
 */
void Plane::addFlight(Flight *flight) {
    Flight::incrementFlightCounter(); //Increments the flight ID here only when it is certain to be a real flight
    flight->setPlanePlate(registration_plate); //Stores in the flight the plate of the plane as a unique identifier
    this->flight_plan.push_back(flight);
}

void Plane::addFlights(list<Flight *> &flights) {
    for (Flight* &flight: flights){
        configureFlight(flight);
        this->flight_plan.push_back(flight);
    }
}


/**
 * Remove a flight form the flight_plan given its number
 * @param number
 * @return true if the flight is found and removed
 */
bool Plane::removeFlight(unsigned int number) {
    for (auto it = flight_plan.begin(); it != flight_plan.end() ; it++){
        if ((*it)->getNumber() == number){
            flight_plan.erase(it);
            return true;
        }
    }
    return false;
}
/**
 *
 * @param numbers
 * @return true if all planes are removed successfully
 */
bool Plane::removeFlights(const std::vector<unsigned int>& numbers) {
    bool flag = true;
    for (auto n: numbers){
        if (!removeFlight(n)) flag = false;
    }
    return flag;
}

void Plane::alterFlightDuration(unsigned int number, unsigned int new_duration) {
    for (auto & it : flight_plan){
        if (it->getNumber() == number){
            it->setDuration(new_duration);
            break;
        }
    }
}

void Plane::alterFlightOrigin(unsigned int number, Airport *new_origin) {
    for (auto & it : flight_plan){
        if (it->getNumber() == number){
            it->setOrigin(new_origin);
            break;
        }
    }
}

void Plane::alterFlightDestination(unsigned int number, Airport *new_destination) {
    for (auto & it : flight_plan){
        if (it->getNumber() == number){
            it->setOrigin(new_destination);
            break;
        }
    }
}

/**
 * Adds a new upcoming service
 * @param service
 */
void Plane::addService(Service* service) {
    upcoming_services.push(service);
}
/**
 * Adds a finished service
 */
void Plane::addFinishedService(Service* service) {
    finished_services.push_back(service);
}
/**
 * Finishes the service at the front of the queue sending it to the finished services
 */
void Plane::finishService() {
    Service* aux = upcoming_services.front();
    upcoming_services.pop();
    finished_services.push_back(aux);

}
/**
 * Prints the seats of one of the planes' flights
 * @param flight
 */
void Plane::showSeats(const Flight& flight) {
    flight.showSeats();
}
/**
 * Gets the flights of the plane that go from an origin to a destination and have at least a number of seats free
 * @param origin
 * @param destination
 * @param number_of_passengers
 * @return
 */
list<Flight *> Plane::getMatchingFlights(Airport *origin, Airport *destination, unsigned number_of_passengers) const {
    list<Flight*> res;
    for (Flight* flight: flight_plan){
        if (flight->notFull(number_of_passengers) && origin == flight->getOrigin() && destination == flight->getDestination()) res.push_back(flight);
    }
    return res;
}
/**
 * Gets the flights of the plane that go from a city to another and have at least a number of seats free
 * @param origin
 * @param destination
 * @param number_of_passengers
 * @return
 */
list<Flight *> Plane::getMatchingFlights(const std::string& origin, const std::string& destination, unsigned number_of_passengers) const {
    list<Flight*> res;
    for (Flight* flight: flight_plan){
        if (flight->notFull(number_of_passengers) && origin == flight->getOrigin()->getCity() && destination == flight->getDestination()->getCity()) res.push_back(flight);
    }
    return res;
}

list<Flight *> Plane::getFlights() const {
    return flight_plan;

}
/**
 * Configures the seats of a flight according to the seat placement of the plane
 * @param flight
 */
void Plane::configureFlight(Flight* flight) {
    flight->configureSeats();
}

/**
 * Adds a service to the upcoming services queue
 * @param service
 */
void Plane::queueService(Service *service) {
    upcoming_services.push(service);
}

/**
 * Remove a service from the upcoming services queue and send it to the finished services
 * @param service
 */
void Plane::dequeueService(Service *service) {
    removeService(service);
    service->setFinished();
    finished_services.push_back(service);
}
/**
 * Finish a certain service
 * @param service
 */
void Plane::removeService(Service* service){
    vector<Service*> aux;
    while (!upcoming_services.empty())
    {
        if(service != upcoming_services.front())aux.push_back(upcoming_services.front());
        upcoming_services.pop();
    }
    for(Service* service1 : aux)
        upcoming_services.push(service1);
}

/**
 * Prints the upcoming services of the plane
 */
void Plane::showUpcomingServices() {
    vector<Service*> aux;
    auto aux_queue = upcoming_services;
    while (!aux_queue.empty())
    {
        aux.push_back(aux_queue.front());
        aux_queue.pop();
    }
    for(Service* service1 : aux){
        cout << "Service:" << std::endl;
        cout << "   -Date: " << service1->getDate().dateStr() << std::endl;
        cout << "   -Worker ID: " << service1->getWorkerId() << std::endl;
        cout << "   -Type: " << service1->getType() << std::endl;
    }
}

/**
 * Prints the finished services of the plane
 */
void Plane::showFinishedServices() {
    for(Service* service1 : finished_services){
        cout << "Service:" << std::endl;
        cout << "   -Date: " << service1->getDate().dateStr() << std::endl;
        cout << "   -Worker ID: " << service1->getWorkerId() << std::endl;
        cout << "   -Type: " << service1->getType() << std::endl;
    }
}
