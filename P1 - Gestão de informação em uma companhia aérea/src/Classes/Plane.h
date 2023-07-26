#ifndef AED2122_PLANE_H
#define AED2122_PLANE_H


#include <string>
#include <vector>
#include <list>
#include <queue>
#include "Flight.h"
#include "Service.h"
#include "Seat.h"
#include <iomanip>
#include <algorithm>

class Plane {

private:
    std::string registration_plate; //Unique identifier of the plane
    std::string plane_type; //Identifies the model of the plane
    unsigned int capacity; //Number of seats
    std::list<Flight *> flight_plan;
    std::queue<Service *> upcoming_services;
    std::vector<Service *> finished_services;
    unsigned int cols, rows; //Number of columns and rows of seats
public:
    Plane(std::string registration_plate, std::string plane_type, unsigned int capacity, unsigned int cols);
    std::string getRegistrationPlate() const;
    std::string getPlaneType() const;
    unsigned int getCapacity() const;
    unsigned int getCols() const;
    void addFlight(Flight *flight);
    void addFlights(list<Flight *> &flights);
    bool removeFlight(unsigned int number);
    bool removeFlights(const std::vector<unsigned int> &numbers);
    void alterFlightDuration(unsigned int number, unsigned int new_duration);
    void alterFlightOrigin(unsigned int number, Airport *new_origin);
    void alterFlightDestination(unsigned int number, Airport *new_destination);
    void addService(Service *service);
    void addFinishedService(Service* service);
    void finishService();
    static void showSeats(const Flight &flight) ;
    static void configureFlight(Flight *flight);
    list<Flight *> getMatchingFlights(Airport *origin, Airport *destination, unsigned int number_of_passengers = 1) const;
    list<Flight *> getMatchingFlights(const std::string &origin, const std::string &destination, unsigned int number_of_passengers = 1) const;
    list<Flight *> getFlights() const;
    void queueService(Service *service);
    void dequeueService(Service *service);
    void removeService(Service *service);
    void showUpcomingServices();
    void showFinishedServices();
};
#endif //AED2122_PLANE_H