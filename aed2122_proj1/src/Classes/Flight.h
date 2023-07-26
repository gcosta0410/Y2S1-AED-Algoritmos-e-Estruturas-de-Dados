#ifndef AED2122_FLIGHT_H
#define AED2122_FLIGHT_H

#include <vector>
#include <queue>
#include "Date.h"
#include "Airport.h"
#include "Seat.h"
#include "Passenger.h"
#include "Luggage.h"
#include "TransportCar.h"


struct CarDimensions{
    unsigned int c, n, m;
};
using namespace std;

class Flight {
private:
    unsigned int number;
    Date DateDeparture;
    Time_m time;
    unsigned int duration;
    unsigned int max_occupation;
    unsigned int current_occupation;
    Airport* origin;
    Airport* destination;
    std::vector<std::vector<Seat>> seats;
    unsigned int cols, rows;
    std::vector<Passenger> passengers;
    string plane_registration_plate;
    TransportCar transport_car;
public:

   Flight(Airport *origin, Airport *destination, unsigned int max_occupation = 0, unsigned int cols = 1, Date departure = Date(
        1, 1, 1), Time_m time = Time_m() ,unsigned int duration = -1,
       unsigned int occupation = 0, const std::vector<Passenger>& passengers = vector<Passenger>(), unsigned int car_c = 2,
       unsigned int car_n = 3, unsigned int car_m = 5);

    unsigned int getNumber() const;
    Airport * getOrigin() const;
    Airport * getDestination() const;
    std::string getPlanePlate() const;
    std::string getTimeStr()const;
    std::vector<Passenger>* getPassengers();
    Date getDateDeparture() const;
    CarDimensions getCarDimensions() const;
    unsigned int getCols() const;
    void setDuration(unsigned int duration);
    void setOrigin(Airport *origin);
    void setPlanePlate(string plate);
    void setTime(Time_m t);
    void setDestination(Airport *destination);
    void setDate(Date date);
    void setMaxOccupation(unsigned int max);
    void setCols(unsigned int cols);
    bool notFull(unsigned int number_of_passengers) const;
    void showSeats() const;
    void showFlight() const;
    void showFlightToPassenger() const;
    void showCar() const;
    bool validSeat(unsigned int seat_number);
    void addPassenger(const Passenger &passenger);
    bool operator==(const Flight& f) const;
    bool addToConveyor(const Luggage& lug);
    void loadToCar();
    void configureSeats();
    static unsigned int flight_counter;
    static void incrementFlightCounter();
};


#endif //AED2122_FLIGHT_H
