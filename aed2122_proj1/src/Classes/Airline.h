#ifndef AED2122_AIRLINE_H
#define AED2122_AIRLINE_H

#include <vector>
#include <set>
#include "Plane.h"

class Airline {

    std::vector<Plane*> planes;
    std::vector<Flight*> flights; //TODO tirar isto?
    std::vector<Airport*> airports;
    std::vector<Service*> services; //TODO tirar isto?
    std::vector<Worker*> workers;
    std::vector<Ticket*> tickets;
    std::set<string> countries_set;
    std::set<string> cities_set;

public:
    Airline();
    std::set<std::string> getCountries() const;
    std::set<std::string> getCities() const;
    void loadAirports();
    void showAirports() const;
    void addAirport(Airport* airport);
    bool removeAirport(const string& name);
    void showAirportByCountry(const vector<string>& countries);
    void showAirportByCity(const vector<string>& cities);
    void addFlight(Flight* flight,Plane* plane);
    void loadFlights();
    void showFlights();
    static void removeAllFlights();
    void storeAllFlights();
    void storeAllTickets();
    void addPlanes(Plane* plane);
    void addPlanes(std::vector<Plane *>& planes_v);
    bool removePlanes(const string& plate);
    bool removePlanes(const std::vector<string>& plates);
    static void removeAllPlanes();
    void storeAllPlanes();
    void loadPlanes();
    void showPlanes() const;
    void showPlanesByCriteria(const string& criteria) const;
    static void removeAllTransports();
    void storeAllTransports();
    void loadTransports();
    void loadTickets();
    void loadServices();
    void loadWorkers();
    void showFlightsByPlate(const vector<string>& plates);
    void showFlightsByArrival(const vector<string>& cities);
    void showFlightsByDeparture(const vector<string>& cities);
    Flight * getFlightById(unsigned int id) const;
    static void removeAllServices();
    void storeAllServices();
    bool removeService(Service* service);
    bool removeWorker(int id);
    static void removeAllWorkers();
    void storeAllWorkers();
    void addWorker(const string& name);
    bool workerExists(int id);
    void showWorkers();
    void showWorkersAZ();
    void showWorkersZA();

    std::vector<Plane *> getPlanes();
    std::vector<Airport *> getAirports();

    list<Flight *> getMatchingFlights(Airport *origin, Airport *destination, unsigned int number_of_passengers) const;
    list<Flight *> getMatchingFlights(const std::string &origin, const std::string &destination, unsigned int number_of_passengers) const;

    static void removeAllAirports();
    void storeAllAirports();

    void newPassengers();
    static int askNumberOfPeople() ;
    void askForLuggage(list<Passenger> &passengers, Flight *chosen_flight, const vector<unsigned int> &chosen_seats);
    static vector<unsigned int> askPassengerSeats(list<Passenger> &passengers, Flight *chosen_flight) ;
    Plane * getPlane(const string& plate);
    Airport * getAirport(const std::string& name);
    void searchMeansOfTransport() const;

    static list<Passenger> askPassengerNames(int number_of_people) ;
    static Flight *chooseFlight(const list<Flight *> &flight_options) ;
    Flight *chooseFlight() const;
    list<Flight *> &searchFlights(list<Flight *> &flight_options, int number_of_people) const;

    bool airportExists(const string &name) const;
    bool planeExists(const string &plate);
    bool departureCityExists(const string& city);
    bool arrivalCityExists(const string& city);
    bool removeFlight(const string& departure, const string& arrival, const string& planePlate, Date date);
    void removeFlights(const string &airportName);
    bool updateFlightDestination(unsigned int flight_id, const std::string& apt_name);
    bool updateFlightTime(unsigned int flight_id, Time_m t);
    bool updateFlightDate(unsigned int flight_id, Date d);
    void updateFlight();
    static void removeAllTickets();

    void showServices();
    void addService(Service* service);
    void addToUpcomingServices(Service* service);
    void addToFinishedServices(Service* service);
    void showUpcomingServices(const string& plate);
    void showFinishedServices(const string& plate);

    void showPassengers();
    void showPassengersByFlightAZ();
    void showPassengersByFlightZA();

    void removeTickets(const string &airport_name);
    void removeTickets(const int &id);
    void removeFlightsofPlaneandTickets(const string& plate);

};


#endif //AED2122_AIRLINE_H
