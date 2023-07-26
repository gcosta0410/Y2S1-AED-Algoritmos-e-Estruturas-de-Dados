#include <fstream>
#include <algorithm>
#include <sstream>
#include "Airline.h"
#include "Passenger.h"
#include "AuxiliaryFunctions.h"
#include "Ticket.h"
#include "menu.h"

Airline::Airline() = default;

std::set<std::string> Airline::getCountries() const{
    return this->countries_set;
}

std::set<std::string> Airline::getCities() const{
    return this->cities_set;
}

/**
 * Reads all the information from airports, creating the corresponding objects
 */
void Airline::loadAirports() {
    if(!airports.empty()) airports.clear();

    // Create a text std::string, which is used to output the text file
    std::string line, next;

    // Read from the planes.txt text file
    std::ifstream airportsfile("TextFiles/airports.txt");

    // Read the file, line by line
    while(std::getline(airportsfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;

        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }

        std::string name = values.at(0), city = values.at(1), country = values.at(2);

        cities_set.insert(city);
        countries_set.insert(country);

        auto* airport = new Airport(name,country,city);
        this->airports.push_back(airport);
    }
    airportsfile.close();
}

/**
 * Adds an airport to the vector of airports and to the airports file
 * @param airport
 */
void Airline::addAirport(Airport* airport){
    airports.push_back(airport);
    std::ofstream airportsfile("TextFiles/airports.txt",std::ios::app);
    std::string info = airport->getName() + "," + airport->getCity() + "," + airport->getCountry() + "\n";
    airportsfile << info;
    airportsfile.close();
    loadAirports();
}
/**
 * Prints the information of all airports
 */
void Airline::showAirports() const{
    std::cout <<"There are " << airports.size() << " airports" << endl;
    for(Airport *airport : airports){
        std::cout << "Airport: " << std::endl;
        std::cout << "    Name: " << airport->getName() << std::endl;
        std::cout << "    Country: " << airport->getCountry() << std::endl;
        std::cout << "    City: " << airport->getCity() << std::endl;
    }
}
/**
 * Removes an airport updating all objects and files that have any dependency
 * @param name
 * @return
 */
bool Airline::removeAirport(const string& name){
    for (int i = 0; i < airports.size() ; i++){
        if (airports[i]->getName() == name){
            //delete airports[i];
            //airports[i] = nullptr;
            airports.erase(airports.begin() + i);
            //Remove all tickets that flew to or from that airport
            removeTickets(name);
            removeAllTickets();
            storeAllTickets();
            loadTickets();
            //Remove all flights to and from the airport
            removeFlights(name);
            removeAllFlights();
            storeAllFlights();
            loadFlights();
            //Remove all services that could depend on the previous objects
            removeAllServices();
            storeAllServices();
            loadServices();
            //Remove all transports from the airport
            removeAllTransports();
            storeAllTransports();
            loadTransports();
            //Update the airports file
            removeAllAirports(); //clears the file
            storeAllAirports(); //rewrites the file with the updated info
            loadAirports();
            return true;
        }
    }
    return false;
}
/**
 * Show info from airports in a certain country
 * @param countries
 */
void Airline::showAirportByCountry(const vector<string>& countries){
    vector<Airport> airportsAux;
    for(auto airport : this->airports){
        string aux = airport->getCountry();
        for(const auto& country : countries){
            if(country == aux) {airportsAux.push_back(*airport); break;}
        }
    }
    auto i = airportsAux.size();
    if(i == 0) cout << "There are no Airports in the selected countries!" << std::endl;
    else if( i == 1) cout << "There is 1 Airport." << std::endl;
    else{
        cout << "There are " << airportsAux.size() << " Airports." << std::endl;
    }
    for(const auto& aux : airportsAux){
        std::cout << "Airport: " << std::endl;
        std::cout << "    Name: " << aux.getName() << std::endl;
        std::cout << "    Country: " << aux.getCountry() << std::endl;
        std::cout << "    City: " << aux.getCity() << std::endl;
    }
}

/**
 * Show info from airports in a certain city
 * @param cities
 */
void Airline::showAirportByCity(const vector<string>& cities){
    vector<Airport> airportsAux;
    for(auto airport : this->airports){
        string aux = airport->getCity();
        for(const auto& city : cities){
            if(city == aux) {airportsAux.push_back(*airport); break;}
        }
    }
    auto i = airportsAux.size();
    if(i == 0) cout << "There are no Airports in the selected cities!" << std::endl;
    else if( i == 1) cout << "There is 1 Airport." << std::endl;
    else{
        cout << "There are " << airportsAux.size() << " Airports." << std::endl;
    }
    for(const auto& aux : airportsAux){
        std::cout << "Airport: " << std::endl;
        std::cout << "    Name: " << aux.getName() << std::endl;
        std::cout << "    Country: " << aux.getCountry() << std::endl;
        std::cout << "    City: " << aux.getCity() << std::endl;
    }
}

/**
 * Add a flight to a plane and writes to the flights file
 * @param flight
 * @param plane
 */
void Airline::addFlight(Flight* flight, Plane* plane) {
    flights.push_back(flight);
    flight->setPlanePlate(plane->getRegistrationPlate());
    std::ofstream flightsfile("TextFiles/flights.txt",std::ios::app);
    std::string day = to_string(flight->getDateDeparture().getDay());
    if(day.length() == 1) day = "0" + day;
    std::string month = to_string(flight->getDateDeparture().getMonth());
    if(month.length() == 1) month = "0" + month;
    std::string info = flight->getOrigin()->getName() + "," + flight->getDestination()->getName() + "," + plane->getRegistrationPlate() + "," +to_string(flight->getDateDeparture().getYear())+ ","
            +month + "," + day + "," + flight->getTimeStr() + "\n";
    flightsfile << info;
    flightsfile.close();
    loadAirports();
}

/**
 * Updates the flights file
 */
void Airline::updateFlight() {
    removeAllFlights();
    storeAllFlights();
}


/**
 * Adds a plane to the airline and updates the planes file
 * @param plane
 */
void Airline::addPlanes(Plane* plane) {
    this->planes.push_back(plane);
    std::ofstream planesfile("TextFiles/planes.txt", std::ios::app);
    std::string info = plane->getRegistrationPlate() + "," + plane->getPlaneType() + "," + to_string(plane->getCapacity()) + "," +
            to_string(plane->getCols()) + "\n";
    planesfile << info;
    planesfile.close();
    this->loadPlanes();
}

/**
 * Adds planes to the airline and updates the planes file
 * @param planes_v
 */
void Airline::addPlanes(std::vector<Plane *> &planes_v) {
    std::ofstream planesfile("TextFiles/planes.txt", std::ios::app);
    for(Plane* plane : planes_v){
        std::string info = plane->getRegistrationPlate() + "," + plane->getPlaneType() + "," + to_string(plane->getCapacity()) + "," +
                           to_string(plane->getCols()) + "\n";
        planesfile << info;
        this->planes.push_back(plane);
    }
    planesfile.close();
    this->loadPlanes();
}


/**
 * Removes a plane from the airline updating all objects and files that have any dependency
 * @param plate
 * @return
 */
bool Airline::removePlanes(const string& plate) {
    for (int i = 0; i < planes.size() ; i++){
        if (planes[i]->getRegistrationPlate() == plate){
            removeFlightsofPlaneandTickets(plate); //remove the flights and tickets
//            delete planes[i];
//            planes[i] = nullptr;
            planes.erase(planes.begin() + i);

            //Update the tickets file
            removeAllTickets();
            storeAllTickets();
            loadTickets();
            //Update the flights file
            removeAllFlights();
            storeAllFlights();
            loadFlights();

            removeAllPlanes(); //clear the file
            storeAllPlanes(); //update the file without the removed plane

            this->loadPlanes();
            return true;
        }
    }
    return false;
}

/**
 * Check if a plane exists
 * @param plate
 * @return
 */
bool Airline::planeExists(const string& plate){
    for (auto & plane : planes){
        if (plane->getRegistrationPlate() == plate){
            return true;
        }
    }
    return false;
}

/**
 * Check if a city is the destination of any flight
 * @param city
 * @return
 */
bool Airline::departureCityExists(const string& city){
    for (auto & flight : flights){
        if (flight->getOrigin()->getCity() == city){
            return true;
        }
    }
    return false;
}

/**
 * Check if a city is the origin of any flight
 * @param city
 * @return
 */
bool Airline::arrivalCityExists(const string& city){
    for (auto & flight : flights){
        if (flight->getDestination()->getCity() == city){
            return true;
        }
    }
    return false;
}



/**
 *
 * @param plates
 * @return true if all planes are removed successfully
 */
//Done: yes
//Tested: yes
bool Airline::removePlanes(const std::vector<string>& plates) {
    bool flag = true;
    for (const string& plate: plates){
        if (!removePlanes(plate)) flag = false;
    }
    return flag;
}


/**
 * Clear the planes file
 */
void Airline::removeAllPlanes(){
    std::ofstream planesfile("TextFiles/planes.txt");
    planesfile.close();
}

/**
 * Write to the planes file all information stored in the objects
 */
void Airline::storeAllPlanes(){
    std::ofstream planesfile("TextFiles/planes.txt", std::ios::app);
    for(Plane* plane : planes){
        std::string info = plane->getRegistrationPlate() + "," + plane->getPlaneType() + "," + to_string(plane->getCapacity()) + "," +
                           to_string(plane->getCols()) + "\n";
        planesfile << info;
    }
    planesfile.close();
}

/**
 * Clear the airports file
 */
void Airline::removeAllAirports(){
    std::ofstream airportsfile("TextFiles/airports.txt");
    airportsfile.close();
}

/**
 * Clear the tickets file
 */
void Airline::removeAllTickets(){
    std::ofstream tickets_file("TextFiles/tickets.txt");
    tickets_file.close();
}

/**
 * Write to the airports file all the information of the airports
 */
void Airline::storeAllAirports(){
    std::ofstream airportsfile("TextFiles/airports.txt", std::ios::app);
    for(Airport* airport : airports){
        std::string info = airport->getName() + "," + airport->getCity() + "," + airport->getCountry() + "\n";
        airportsfile << info;
    }
    airportsfile.close();
}

/**
 * Create planes based on the planes file
 */
void Airline::loadPlanes() {

    if (!planes.empty()) planes.clear();
    // Create a text std::string, which is used to output the text file
    std::string line, next;

    // Read from the planes.txt text file
    std::ifstream planesfile("TextFiles/planes.txt");


    // Read the file, line by line
    while(std::getline(planesfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;

        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }

        std::string plate = values.at(0), type = values.at(1);
        unsigned int capacity = std::stoi(values.at(2));

        auto* plane = new Plane(plate, type, capacity, 4);
        this->planes.push_back(plane);
    }
    planesfile.close();
}

/**
 * Show all planes
 */
void Airline::showPlanes() const {
    int id = 1;
    std::cout <<"There are " << planes.size() << " planes:" << endl;
    for(Plane* plane : planes){
        std::cout << "Plane " << id << std::endl;
        std::cout << "    Registration plate: " << plane->getRegistrationPlate() << std::endl;
        std::cout << "    Plane type: " << plane->getPlaneType() << std::endl;
        std::cout << "    Capacity: " << plane->getCapacity() << std::endl;
        id++;
    }
}

/**
 * Show planes ordered by a criteria: "plate", "tpe" or "capacity"
 * @param criteria
 */
void Airline::showPlanesByCriteria(const string& criteria) const{

    vector<Plane> planesAux;
    for(auto const &plane : this->planes){
        planesAux.push_back(*plane);
    }
    if(criteria == "plate"){
        std::sort(planesAux.begin(), planesAux.end(), comparePlanesByPlate);
    }
    else if(criteria == "type"){
        std::sort(planesAux.begin(), planesAux.end(), comparePlanesByType);
    }
    else if(criteria == "capacity"){
        std::sort(planesAux.begin(), planesAux.end(), comparePlanesByCapacity);
    }
    int id = 1;
    for(const auto& plane : planesAux){
        std::cout << "Plane " << id << std::endl;
        std::cout << "    Registration plate: " << plane.getRegistrationPlate() << std::endl;
        std::cout << "    Plane type: " << plane.getPlaneType() << std::endl;
        std::cout << "    Capacity: " << plane.getCapacity() << std::endl;
        id++;
    }
}

/**
 * Create flights based on the flights file
 */
void Airline::loadFlights() {

    if(!flights.empty()) flights.clear();

    // Create a text std::string, which is used to output the text file
    std::string line, next;

    // Read from the planes.txt text file
    std::ifstream flightsfile("TextFiles/flights.txt");


    // Read the file, line by line
    while(std::getline(flightsfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;

        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }

        std::string origin = values.at(0), destination = values.at(1), plate = values.at(2);
        unsigned int year = std::stoi(values.at(3)), month = std::stoi(values.at(4)), day = std::stoi(values.at(5)),
        car_c = stoi(values.at(7)), car_n = stoi(values.at(8)), car_m = stoi(values.at(9));
        Time_m time = Time_m(values.at(6));
        Plane* p = getPlane(plate);
        Airport* origin_airport = getAirport(origin) ,*destination_airport = getAirport(destination);
        auto* flight = new Flight(origin_airport,destination_airport,p->getCapacity(),p->getCols(),Date(year,month,day),time,5,0,vector<Passenger>(),car_c, car_n, car_m);
        p->addFlight(flight);
        flights.push_back(flight);
    }
    flightsfile.close();
}
/**
 * Show all flights
 */
void Airline::showFlights() {
    auto s = flights.size();
    if(s == 1) std::cout <<"There is " << s << " flight:" << std::string(2,'\n');
    else std::cout <<"There are " << s << " flights:" << std::string(2,'\n');
    for(Flight* flight : flights){
        flight->showFlight();
        std::cout<< std::endl;
    }
}

void Airline::showFlightsByPlate(const vector<string>& plates){
    vector<Flight*> flightsAux;
    for(Flight* flight : flights){
        string aux = flight->getPlanePlate();
        for(const auto& plate : plates){
            if(plate == aux) {flightsAux.push_back(flight); break;}
        }
    }
    std::sort(flightsAux.begin(), flightsAux.end(), [](Flight* f1, Flight* f2){
        if(f1->getPlanePlate() == f2->getPlanePlate()) return f1->getNumber() < f2->getNumber();
        else return (f1->getPlanePlate() < f2->getPlanePlate());
    }
    );

    auto i = flightsAux.size();
    if(i == 0) cout << "There are no Flights matching that plate!" << std::endl;
    else if( i == 1) cout << "There is 1 Flight matching that plate." << std::endl;
    else{
        cout << "There are " << flightsAux.size() << " Flights." << std::endl;
    }
    for(const auto& aux : flightsAux){
        aux->showFlight();
        std::cout<< std::endl;
    }

}

/**
 * Show flights whose destination is one of the given cities ordered alphabetically first then by flight number
 * @param cities
 */
void Airline::showFlightsByArrival(const vector<string>& cities){
    vector<Flight*> flightsAux;
    for(Flight* flight : flights){
        string aux = flight->getDestination()->getCity();
        for(const auto& city : cities){
            if(city == aux) {flightsAux.push_back(flight); break;}
        }
    }
    std::sort(flightsAux.begin(), flightsAux.end(),[](Flight* f1,Flight* f2){
        if(f1->getDestination()->getCity() == f2->getDestination()->getCity()) return f1->getNumber() < f2->getNumber();
        else return f1->getDestination()->getCity() < f2->getDestination()->getCity();
    });
    for(Flight* flight : flightsAux){
        flight->showFlight();
        std::cout<< std::endl;
    }
}

/**
 * Show flights whose origin is one of the given cities ordered alphabetically first then by flight number
 * @param cities
 */
void Airline::showFlightsByDeparture(const vector<string>& cities){
    vector<Flight*> flightsAux;
    for(Flight* flight : flights){
        string aux = flight->getOrigin()->getCity();
        for(const auto& city : cities){
            if(city == aux) {flightsAux.push_back(flight); break;}
        }
    }
    std::sort(flightsAux.begin(), flightsAux.end(),[](Flight* f1,Flight* f2){
        if(f1->getOrigin()->getCity() == f2->getOrigin()->getCity()) return f1->getNumber() < f2->getNumber();
        else return f1->getOrigin()->getCity() < f2->getOrigin()->getCity();
    });
    for(Flight* flight : flightsAux){
        flight->showFlight();
        std::cout<< std::endl;
    }
}

/**
 * Clears the flights file
 */
void Airline::removeAllFlights(){
    std::ofstream flightsfile("TextFiles/flights.txt");
    flightsfile.close();
}

/**
 * Write the information of all flights to the flights file
 */
void Airline::storeAllFlights(){
    std::ofstream flightsfile("TextFiles/flights.txt", std::ios::app);
    for(Flight* flight: flights){
        std::string car_c = to_string(flight->getCarDimensions().c);
        std::string car_m = to_string(flight->getCarDimensions().m);
        std::string car_n = to_string(flight->getCarDimensions().n);
        std::string day = to_string(flight->getDateDeparture().getDay());
        if(day.length() == 1) day = "0" + day;
        std::string month = to_string(flight->getDateDeparture().getMonth());
        if(month.length() == 1) month = "0" + month;
        std::string info;
        info.append(flight->getOrigin()->getName()).append(",").append(flight->getDestination()->getName()).append(",").append(flight->getPlanePlate()).append(",").
        append(to_string(flight->getDateDeparture().getYear())).append(",").append(month).append(",").append(day).append(",").append(flight->getTimeStr()).
        append(",").append( car_c).append(",").append( car_n).append( ",").append(car_m).append("\n");

        flightsfile << info;
    }
    flightsfile.close();
}

/**
 * Write to the tickets file info about the tickets, passengers and respective luggages
 */
void Airline::storeAllTickets(){
    std::ofstream flightsfile("TextFiles/tickets.txt", std::ios::app);


    for(auto ticket: tickets){
        std::string flight_id = to_string(ticket->getFlightId()),passenger_id = to_string(ticket->getPassengerId()),
        seat_number = to_string(ticket->getSeat()), luggage_weight = to_string(ticket->luggageWeight());
        std::string passenger_name = ticket->getPassengerName();
        std::string luggage_q = ticket->luggageIsInCar() ? "T": "F";

        std::string info;
        info.append(flight_id).append(",").append(passenger_id).append(",").append(passenger_name).append(",").append(seat_number).append(",").append(luggage_weight).append(",").append(luggage_q).append("\n");
        flightsfile << info;
    }
    flightsfile.close();
}

std::vector<Plane *> Airline::getPlanes() {
    return this->planes;
}

std::vector<Airport *> Airline::getAirports() {
    return this->airports;
}

/**
 * Get flights that depart today or later from an origin airport, arrive at a destination airport and have at least a number of seats available
 * @param origin
 * @param destination
 * @param number_of_passengers
 * @return
 */
list<Flight *> Airline::getMatchingFlights(Airport *origin, Airport *destination, unsigned int number_of_passengers) const {

    list<Flight*> res;
    for(Flight* flight: flights){
        if (getDateNow() <= flight->getDateDeparture() && flight->notFull(number_of_passengers) && *origin == *(flight->getOrigin()) && *destination == *(flight->getDestination())) res.push_back(flight);
    }
    return res;
}

/**
  * Get flights that depart today or later from an origin city, arrive at a destination city and have at least a number of seats available
 * @param origin
 * @param destination
 * @param number_of_passengers
 * @return
 */
list<Flight *> Airline::getMatchingFlights(const std::string &origin, const std::string &destination, unsigned int number_of_passengers) const {

    list<Flight*> res;
    for(Flight* flight: flights){
        if (getDateNow() <= flight->getDateDeparture() && flight->notFull(number_of_passengers) && origin == (flight->getOrigin()->getCity()) && destination == flight->getDestination()->getCity()) res.push_back(flight);

    }
    return res;
}

/**
 * Ask one or more passengers where they want to go and help them select a flight
 */
void Airline::newPassengers()  {
    int number_of_people = askNumberOfPeople();
    list<Passenger> passengers = askPassengerNames(number_of_people);
    list<Flight*> flight_options;
    searchFlights(flight_options, number_of_people);
    Flight *chosen_flight = chooseFlight(flight_options);
    vector<unsigned int> chosen_seats = askPassengerSeats(passengers, chosen_flight);
    askForLuggage(passengers, chosen_flight, chosen_seats);
    std::cout << "Have a nice flight!!" << std::string (2, '\n');
    std::cin.ignore(1000,'\n');
}

/**
 * Ask the origin and destination to show the available flights
 * @param flight_options
 * @param number_of_people
 * @return
 */
list<Flight *> &Airline::searchFlights(list<Flight *> &flight_options, int number_of_people) const {
    bool flight_found = false;
    while(!flight_found) {
        cout << "Do you want search by airport name or city? (Answer 'city' or 'name')" << endl;
        string search_filter;
        getline(cin, search_filter);
        while(!(search_filter == "city" || search_filter == "name")){
            cout << "Please enter a valid option. (Answer 'city' or 'name')" << endl;
            getline(cin, search_filter);
        }
        if (search_filter == "name") {
            cout << "You are searching for the name of the airports" << string(2, '\n');
            cout << "Where will you start the trip?" << endl << ">";
            string origin;
            getline(cin, origin);
            cout << "And where do you want to go?" << endl << ">";
            string destination;
            getline(cin, destination);
            flight_options = getMatchingFlights(new Airport(origin), new Airport(destination), number_of_people);
            if(flight_options.empty()){
                cout << "Sorry! Could not find a flight for you." << endl << "Please try again." << endl << ">";
            }
            else flight_found = true;
        }
        else{
            cout << "You are searching for the city of the airports" << string(2, '\n');
            cout << "Where will you start the trip?" << endl << ">";
            string origin_city;
            getline(cin, origin_city);
            cout << "And where do you want to go?" << endl << ">";
            string destination_city;
            getline(cin, destination_city);
            flight_options = getMatchingFlights(origin_city, destination_city, number_of_people);
            if(flight_options.empty()){
                cout << "Sorry! Could not find a flight for you." << endl << "Please try again." << endl << ">";
            }
            else flight_found = true;
        }
    }
    return flight_options;
}

/**
 * Ask the passengers if they carry luggage and want to automatically check it in
 * @param passengers
 * @param chosen_flight
 * @param chosen_seats
 */
void Airline::askForLuggage(list<Passenger> &passengers, Flight *chosen_flight, const vector<unsigned int> &chosen_seats)  {
    int c = 0;
    for(auto it = passengers.begin(); it != passengers.end(); it++, c++){
        cout <<(*it).getName()<<", do you want to include luggage? ('Y' / 'N')  " << endl << ">";
        bool answer = getAnswer();
        if(!answer){ //No luggage
            auto ticket = new Ticket(chosen_flight->getNumber(),chosen_seats[c], it->getId(), it->getName(), Luggage(
                    it->getId(), 0, false)); //Weight 0 represents no luggage
            it->giveTicket(ticket); //The passenger is given their ticket
            tickets.push_back(ticket);
        }

        else{ //Including luggage

            cout << (*it).getName() << ", how much does it weigh?" << endl << ">";
            unsigned int weight = getUnsignedInt();
            cout <<  (*it).getName() <<", do you want your luggage checked-in automatically? ('Y' / 'N')" << endl << ">";
            bool auto_check_in_answer = getAnswer();
            if(answer) { //Load the luggage into the conveyor and transport car if not full yet
                Luggage luggage = Luggage((*it).getId(), weight, true);
                auto ticket = new Ticket(chosen_flight->getNumber(),chosen_seats[c], it->getId(), it->getName() ,luggage);
                it->giveTicket(ticket);
                tickets.push_back(ticket);
                bool car_is_full = !chosen_flight->addToConveyor(luggage); //Checks if there is still room for the luggage
                if (car_is_full) cout << "Sorry, we were unable to add your luggage. The transport car is already full." << endl;
                else{chosen_flight->loadToCar();}
            }
            else{
                Luggage luggage = Luggage((*it).getId(), weight, false);
                auto ticket = new Ticket(chosen_flight->getNumber(),chosen_seats[c], it->getId(), it->getName() ,luggage);
                it->giveTicket(ticket);
                tickets.push_back(ticket);

            }
        }
        //Update the tickets file
        removeAllTickets();
        storeAllTickets();

    }
}

/**
 * The passengers choose a flight from a list of options
 * @param flight_options
 * @return
 */
Flight *Airline::chooseFlight(const list<Flight *> &flight_options) {
    std::cout << "Please choose one of the following flights:" << endl;
    for (Flight *flight: flight_options) {
        flight->showFlightToPassenger(); //Show the information of the flight
        std::cout << endl;
    }
    std::cout << "Flight no.: ";
    int chosen_number = getInt();


    Flight *chosen_flight = findInList(flight_options, chosen_number);
    bool valid_flight = !(*(chosen_flight) == *(new Flight(new Airport(), new Airport())));
    while (!valid_flight) {
        std::cout << "Please choose a valid flight." << std::endl << "Flight no.: ";
        chosen_number = getInt();
        chosen_flight = findInList(flight_options, chosen_number);
        valid_flight = !(*(chosen_flight) == *(new Flight(new Airport(), new Airport())));
    }
    return chosen_flight;
}

/**
 * Choose a flight out of all the flights available in the airline
 * @return
 */
Flight *Airline::chooseFlight() const{
    for (Flight *flight: flights) {
        flight->showFlight();
        std::cout << endl;
    }
    std::cout << "Flight no.: ";
    int chosen_number = getInt();
    std::list<Flight*> fls(flights.begin(), flights.end());
    Flight *chosen_flight = findInList(fls, chosen_number);
    bool valid_flight = !(*(chosen_flight) == *(new Flight(new Airport(), new Airport())));
    while (!valid_flight) {
        std::cout << "Please choose a valid flight." << std::endl << "Flight no.: ";;
        chosen_number = getInt();
        chosen_flight = findInList(fls, chosen_number);
        valid_flight = !(*(chosen_flight) == *(new Flight(new Airport(), new Airport())));
    }
    return chosen_flight;

}

/**
 * Show the passengers the available seats so they can choose their seat
 * @param passengers
 * @param chosen_flight
 * @return
 */
vector<unsigned int> Airline::askPassengerSeats(list<Passenger> &passengers, Flight *chosen_flight) {
    vector<unsigned int> chosen_seats;
    for(auto & passenger:passengers){
        chosen_flight->showSeats();
        std::cout << (passenger.getName()) << ", please choose an available seat." << std::endl << ">";
        unsigned int chosen_seat = getUnsignedInt();
        bool valid_seat = chosen_flight->validSeat(chosen_seat);
        while (!valid_seat) {
            std::cout << (passenger.getName()) << ", please choose a valid seat." << std::endl << ">";
            chosen_seat = getUnsignedInt();
            valid_seat = chosen_flight->validSeat(chosen_seat);
        }
        chosen_seats.push_back(chosen_seat);
    }

    for (auto &passenger: passengers) {
        chosen_flight->addPassenger(passenger); //Add passenger to the list of passengers of the chosen flight
    }
    return chosen_seats;
}

/**
 * Ask for the names of the passengers
 * @param number_of_people
 * @return
 */
list<Passenger> Airline::askPassengerNames(int number_of_people) {
    list<Passenger> passengers;
    if (number_of_people == 1) cout<<"What is your name?" << endl;
    else cout<<"What are your names?" << endl;
    std::string name;
    for(int i = 0; i< number_of_people; i++){
        std::getline(std::cin, name);
        if (std::cin.eof()) {
            Menu::exitMenu();
        }
        passengers.emplace_back(name);
    }
    return passengers;
}

/**
 * Ask how many people want to buy a ticket
 * @return
 */
int Airline::askNumberOfPeople() {
    cout << "Hello! Please enter the number of people that require a ticket (1 or more)." << endl << ">";
    int number_of_people = getInt();
    while(number_of_people < 1){
        cout << "Please enter a number bigger than 0." << endl << ">";
        number_of_people = getInt();

    }
    return number_of_people;
}

Plane* Airline::getPlane(const string& plate) {
    for(auto & plane : this->planes){
        if(plane->getRegistrationPlate() == plate) return plane;
    }
    return new Plane("","",0,0);
}

Airport * Airline::getAirport(const std::string& name) {
    for(auto & airport : this->airports){
        if(airport->getName() == name) return airport;
    }
    return new Airport(name);
}

/**
 * Ask for an airport to show which transports are available nearby.
 * The passenger can filter and sort the transports they want to see
 */
void Airline::searchMeansOfTransport() const {
    std::string airport_name;
    std::cout << "Do you want to search for transports near which airport?" << std::endl;
    std::getline(std::cin, airport_name);
    while(!airportExists(airport_name)){
        std::cout << "Airport does not exist. Try Again!" << endl;
        std::cout << "Airport:";
        std::getline(std::cin, airport_name);
    }
    bool flag = false;
    for(Airport* apt: airports){
        flag = true;
        if(apt->getName() == airport_name){
            if(apt->noTransports()) {
                std::cout << "We are sorry, but there are no transports near that airport." << std::endl;
                break;
            }
            std::cout << "How do you want to filter the results?" << std::endl
            << "'proximity' to show transports sorted by proximity;" << std::endl
            << "'type' to show transports sorted by type (bus, metro or train) and proximity." << std::endl
            << ">";
            std::string filter = getString();
            while(!(filter == "all" || filter == "type" || filter == "proximity" )){
                std::cout << "Please choose between 'upcoming', 'proximity' and 'type'." << std::endl << ">";
                filter = getString();
            }
            std::cout << "How many transports do you want to see? (Enter '0' to show all or '-1' to use default." << std::endl;
            int number = getInt();
            while (number < -1){
                std::cout << "Number not valid! Try again." <<std::endl << ">";
                number = getInt();
            }
            if(filter == "type"){
                std::cout << "Please choose between 'bus', 'metro' and 'train'." << std::endl << ">";
                std::string vehicle = getString();
                while(!(vehicle == "bus" || vehicle == "metro" || vehicle == "train")){
                    std::cout << "Please choose between 'bus', 'metro' and 'train'." << std::endl << ">";
                    vehicle = getString();
                }
                apt->showTransports(vehicle, number);
            }
            else if(filter == "proximity"){
                apt->showTransports(number);
            }
//            else if(filter == "upcoming"){
//                apt->showTransportsByTime(number);
//            }

            break;
        }
    }
    if (!flag) std::cout << "Sorry, we could not find that Airport." <<std::endl;

}

/**
 * Check if an airport named "name" exists
 * @param name
 * @return
 */
bool Airline::airportExists(const string &name) const {
    for(auto i : this->airports) if(name == i->getName()) return true;
    return false;
}


/**
 * Remove a flight that matches the given information
 * @param departure
 * @param arrival
 * @param planePlate
 * @param date
 * @return
 */
bool Airline::removeFlight(const string& departure, const string& arrival, const string& planePlate, Date date) {
    for (int i = 0; i < flights.size() ; i++){
        if (flights[i]->getOrigin()->getName() == departure && flights[i]->getDestination()->getName() == arrival && flights[i]->getPlanePlate() == planePlate && flights[i]->getDateDeparture() == date){
//            delete flights[i];
//            flights[i] = nullptr;
            flights.erase(flights.begin() + i); //Remove the flight from the management system
            //Remove ticket from the management system
            removeTickets(flights[i]->getNumber());
            //Update tickets infp on file
            removeAllTickets();
            storeAllTickets();
            loadTickets();

            removeAllFlights(); //Clears the flights file
            storeAllFlights(); //Writes to the file without the removed flight
            loadFlights(); //Reads flights from file
            return true;
        }
    }
    return false;
}

/**
 * Create the services present in the services file
 */
void Airline::loadServices() {
    if (!services.empty()) services.clear();
    // Create a text std::string, which is used to output the text file
    std::string line, next;

    // Read from the planes.txt text file
    std::ifstream servicesfile("TextFiles/services.txt");


    // Read the file, line by line
    while(std::getline(servicesfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;

        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }

        std::string plate = values.at(0), type = values.at(5);
        Date date = Date(std::stoi(values.at(1)), std::stoi(values.at(2)),std::stoi(values.at(3)));
        int worker_id = std::stoi(values.at(4));
        bool finished;
        istringstream(values.at(6)) >> finished;
        auto* service = new Service(plate, date, worker_id, type, finished);
        for(Plane* plane : planes) if(plane->getRegistrationPlate() == plate){
            if(!service->isFinished())plane->addService(service);
            else plane->addFinishedService(service);
        }
        this->services.push_back(service);
    }
    servicesfile.close();
}

/**
 * Clear the services file
 */
void Airline::removeAllServices(){
    std::ofstream servicesfile("TextFiles/services.txt");
    servicesfile.close();
}

/**
 * Write to the file all created services
 */
void Airline::storeAllServices(){
    std::ofstream servicesfile("TextFiles/services.txt", std::ios::app);
    for(Service* service: services){
        string plate = service->getPlanePlate();
        string year = to_string(service->getDate().getYear());
        string month = to_string(service->getDate().getMonth());
        string day = to_string(service->getDate().getDay());
        string worker_id = to_string(service->getWorkerId());
        string type = service->getType();
        string finished = (service->isFinished() ? "1":"0");
        std::string info;
        info.append(plate).append(",").append(year).append(",").append(month).append(",").append(day).append(",").append(worker_id).append(",").append(type).append(",").append(finished).append("\n");
        servicesfile << info;
    }
    servicesfile.close();
}

/**
 *
 * @param service
 * @return
 */
bool Airline::removeService(Service* service) {
    string plate = service->getPlanePlate();
    for(Plane *plane : planes) if (plane->getRegistrationPlate() == plate) plane->removeService(service);
    for (int i = 0; i < services.size() ; i++){
        if (*services[i] == *service){
            //delete services[i];
            //services[i] = nullptr;
            services.erase(services.begin() + i); //Remove the service from the management system

            removeAllServices(); //Clear the file
            storeAllServices(); //Write to the file
            loadServices();
            return true;
        }
    }
    return false;
}

/**
 *
 * @param flight_id
 * @param apt_name
 * @return true if the flight exists
 */
bool Airline::updateFlightDestination(unsigned int flight_id, const std::string& apt_name) {
    bool apt_exists = airportExists(apt_name);

    if (!apt_exists){
        std::cout << "Sorry, we do not fly to that airport." << std::endl;
        return false;
    }
    for(auto flight: flights){
        if (flight->getNumber() == flight_id){
            flight->setDestination(getAirport(apt_name));
            return true;
        }
    }
    std::cout << "Sorry, we could not find a flight with that number." << std::endl;
    return false;
}

/**
 *
 * @param flight_id
 * @param t
 * @return true if the flight exists
 */
bool Airline::updateFlightTime(unsigned int flight_id, Time_m t) {
    for(auto flight: flights){
        if (flight->getNumber() == flight_id){
            flight->setTime(t);
            return true;
        }
    }
    std::cout << "Sorry, we could not find a flight with that number." << std::endl;
    return false;
}

/**
 *
 * @param flight_id
 * @param d
 * @return true if the flight exists
 */
bool Airline::updateFlightDate(unsigned int flight_id, Date d) {
    for(auto flight: flights){
        if (flight->getNumber() == flight_id){
            flight->setDate(d);
            return true;
        }
    }
    std::cout << "Sorry, we could not find a flight with that number." << std::endl;
    return false;
}

/**
 * Create the transports present in the transports file
 */
void Airline::loadTransports() {
    for(Airport* airport: airports) if(!airport->getTransports().isEmpty()) airport->emptyTransports();
    // Create a text std::string, which is used to output the text file
    std::string line, next, airportname;

    // Read from the planes.txt text file
    std::ifstream transportsfile("TextFiles/transports.txt");

    // Read the file, line by line
    while(std::getline(transportsfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;
        std::getline(ss, airportname,',');
        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }
        for(int i = 0; i < values.size();i+=5){

            std::string tipoTransport = values.at(i), distancia = values.at(i+1);
            std::string horarioInicial = values.at(i+2), horarioFinal = values.at(i+3), duracao = values.at(i+4);
            std::vector<Time_m>  horario = createSchedule(horarioInicial,horarioFinal,duracao);
            MeanOfTransport m = MeanOfTransport(tipoTransport,stoi(distancia),horario,horarioInicial,horarioFinal,duracao);
            Airport *airport = getAirport(airportname);
            airport->addMeanOfTransport(m);
        }

    }
    transportsfile.close();
}

/**
 * Clear the transports file
 */
void Airline::removeAllTransports() {
    std::ofstream transportsfile("TextFiles/transports.txt");
    transportsfile.close();
}

/**
 * Write the created transports to the transports file
 */
void Airline::storeAllTransports() {
    std::ofstream transportsfile("TextFiles/transports.txt", std::ios::app);
    for(Airport*airport : airports){
        std::string info = airport->getName();
        BSTItrIn<MeanOfTransport> itr(airport->getTransports());
        while(!itr.isAtEnd()){
            info += "," + itr.retrieve().getType() + "," + to_string(itr.retrieve().getDistance()) + "," +
                    itr.retrieve().getInitialHour() + "," + itr.retrieve().getFinalHour() + "," + itr.retrieve().getDuration();
            itr.advance();
        }
        transportsfile << info << "\n";
    }
    transportsfile.close();
}

/**
 * Clear the workers file
 */
void Airline::removeAllWorkers() {
    std::ofstream workersfile("TextFiles/workers.txt");
    workersfile.close();
}
/**
 * Write the created workers to the workers file
 */
void Airline::storeAllWorkers() {
    std::ofstream workersfile("TextFiles/workers.txt", std::ios::app);
    for(Worker* worker: workers){
        string name = worker->getName();
        string id = to_string(worker->getId());
        std::string info = id + ',' + name + "\n";
        workersfile << info;
    }
    workersfile.close();
}

/**
 *
 * @param id
 * @return if worker id exists
 */
bool Airline::removeWorker(int id){
    for (int i = 0; i < workers.size() ; i++){
        if (workers[i]->getId() == id){
            //delete workers[i];
            //workers[i] = nullptr;
            workers.erase(workers.begin() + i); //Remove worker from the management system

            removeAllWorkers(); //Clears the file
            storeAllWorkers(); //Writes to the file
            loadWorkers(); //Reads workers from the file
            return true;
        }
    }
    return false;
}

/**
 * Create the workers present in the workers file
 */
void Airline::loadWorkers() {
    if (!workers.empty()){
        workers.clear();
        Worker::resetId();
    }
    // Create a text std::string, which is used to output the text file
    std::string line, next;

    // Read from the planes.txt text file
    std::ifstream workersfile("TextFiles/workers.txt");

    // Read the file, line by line
    while(std::getline(workersfile, line)){

        std::stringstream ss(line);
        std::vector<std::string> values;

        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }
        string name = values.at(1);
        auto* worker = new Worker(name);
        this->workers.push_back(worker);
    }
    workersfile.close();
}

/**
 * Create the tickets and passengers, luggages present in the tickets file
 */
void Airline::loadTickets() {
    if (!tickets.empty()) tickets.clear();
    // Create a text std::string, which is used to output the text file
    std::string line, next, flight_id;

    std::ifstream tickets_file("TextFiles/tickets.txt");

    // Read the file, line by line
    while (std::getline(tickets_file, line)) {

        std::stringstream ss(line);
        std::vector<std::string> values;
        std::getline(ss, flight_id, ',');
        // Separate each line by ","
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            values.push_back(substr);
        }
        for (int i = 0; i < values.size(); i += 5) {
            std::string passenger_id = values.at(i), passenger_name = values.at(i + 1),
                    seat_number = values.at(i + 2), luggage_weight = values.at(i + 3);
            bool luggage_q = values.at(i + 4) == "T";
            Luggage lug(stoi(passenger_id), stoi(luggage_weight), luggage_q);
            auto p = Passenger(passenger_name);
            auto t = new Ticket(stoi(flight_id), stoi(seat_number), stoi(passenger_id), passenger_name, lug);
            p.giveTicket(t);
            auto flight = getFlightById(stoi(flight_id));
            flight->addPassenger(p);
            flight->validSeat(stoi(seat_number));
            flight->addToConveyor(lug); flight->loadToCar();
            this->tickets.push_back(t);
        }
    }
    tickets_file.close();
}
/**
 * Add worker to the workers file and to the airline
 * @param name
 */
void Airline::addWorker(const string& name){
    auto* new_worker = new Worker(name);
    this->workers.push_back(new_worker);
    std::ofstream workersfile("TextFiles/workers.txt", std::ios::app);
    std::string info = to_string(new_worker->getId())+','+new_worker->getName()+'\n';
    workersfile << info;
    workersfile.close();
    this->loadWorkers();
}
/**
 *
 * @param id
 * @return true if worker exists
 */
bool Airline::workerExists(int id) {
    for(Worker* worker : workers){
        if(worker->getId() == id) return true;
    }
    return false;
}

/**
 * Show workers ordered by ID
 */
void Airline::showWorkers() {
    std::cout <<"There are " << workers.size() << " workers" << endl;
    std::sort(workers.begin(), workers.end(),[](Worker* w1, Worker* w2){
        return w1->getId() < w2->getId();
    });
    for(Worker *worker : workers){
        std::cout << "Worker: " << std::endl;
        std::cout << "    ID: " << worker->getId() << std::endl;
        std::cout << "    Name: " << worker->getName() << std::endl;
    }
}

/**
 * Show workers ordered alphabetically
 */
void Airline::showWorkersAZ() {
    std::cout <<"There are " << workers.size() << " workers" << endl;
    std::sort(workers.begin(), workers.end(),[](Worker* w1, Worker* w2){
        return w1->getName() < w2->getName();
    });
    for(Worker *worker : workers){
        std::cout << "Worker: " << std::endl;
        std::cout << "    ID: " << worker->getId() << std::endl;
        std::cout << "    Name: " << worker->getName() << std::endl;
    }
}

/**
 *  Show workers ordered by reverse alphabetical order
 */
void Airline::showWorkersZA() {
    std::cout <<"There are " << workers.size() << " workers" << endl;
    std::sort(workers.begin(), workers.end(),[](Worker* w1, Worker* w2){
        return w1->getName() > w2->getName();
    });
    for(Worker *worker : workers){
        std::cout << "Worker: " << std::endl;
        std::cout << "    ID: " << worker->getId() << std::endl;
        std::cout << "    Name: " << worker->getName() << std::endl;
    }
}

Flight *Airline::getFlightById(unsigned int id) const {
    for(auto flight: flights){
        if(flight->getNumber() == id){
            return flight;
        }
    }
    return new Flight(new Airport(), new Airport());
}

/**
 * Show passengers ordered by ID
 */
void Airline::showPassengers() {
    std::vector<Passenger> res;
    for(auto flight:flights){
        for(const auto& passenger:*flight->getPassengers()){
            res.push_back(passenger);
        }
    }
    sort(res.begin(), res.end(), [](const Passenger& p1, const Passenger& p2){
        return p1.getId() < p2.getId();
    });
    for(const auto& passenger: res){
        std::cout << "Passenger: " << std::endl;
        std::cout << "    ID: " << passenger.getId() << std::endl;
        std::cout << "    Name: " << passenger.getName() << std::endl;
    }
}


/**
 *  Show passengers ordered by alphabetical order
 */
void Airline::showPassengersByFlightAZ() {
    std::list<Flight*> fls = std::list<Flight*>(flights.begin(), flights.end());
    Flight* chosen_flight = chooseFlight(fls);
    std::vector<Passenger>* passengers = chosen_flight->getPassengers();
    std::cout <<"There are " << passengers->size() << " passengers in flight no." << chosen_flight->getNumber() << endl;
    std::sort(passengers->begin(), passengers->end(),[](const Passenger& p1, const Passenger& p2){
        return p1.getName() < p2.getName();
    });
    for(const auto& passenger: *passengers){
        std::cout << "Passenger: " << std::endl;
        std::cout << "    ID: " << passenger.getId() << std::endl;
        std::cout << "    Name: " << passenger.getName() << std::endl;
    }
}
/**
 *  Show passengers ordered by reverse alphabetical order
 */
void Airline::showPassengersByFlightZA() {
    std::list<Flight*> fls = std::list<Flight*>(flights.begin(), flights.end());
    Flight* chosen_flight = chooseFlight(fls);
    std::vector<Passenger>* passengers = chosen_flight->getPassengers();
    std::cout <<"There are " << passengers->size() << " passengers in flight no." << chosen_flight->getNumber() << endl;
    std::sort(passengers->begin(), passengers->end(),[](const Passenger& p1, const Passenger& p2){
        return p2.getName() < p1.getName();
    });
    for(const auto& passenger: *passengers){
        std::cout << "Passenger: " << std::endl;
        std::cout << "    ID: " << passenger.getId() << std::endl;
        std::cout << "    Name: " << passenger.getName() << std::endl;
    }
}

/**
 * Show all services
 */
void Airline::showServices() {
    std::cout <<"There are " << services.size() << " services" << endl;
    for(Service *service : services){
        std::cout << "Service: " << std::endl;
        std::cout << "    Serviced Plane: " << service->getPlanePlate() << std::endl;
        std::cout << "    Date: " << service->getDate().dateStr() << std::endl;
        std::cout << "    Worker ID: " << service->getWorkerId() << std::endl;
        std::cout << "    Service Type: " << service->getType() << std::endl;
        std::cout << "    Finished: " << ((service->isFinished()) ? "Yes":"No") << std::endl;
    }
}

/**
 * Add a service to the services files and to the airline
 * @param service
 */
void Airline::addService(Service *service) {
    this->services.push_back(service);
    std::ofstream servicesfile("TextFiles/services.txt", std::ios::app);
    std::string info = service->getPlanePlate()+','+service->getDate().dateStrLoad()+','+to_string(service->getWorkerId())+','+service->getType()+','+(service->isFinished() ? "1":"0")+'\n';
    servicesfile << info;
    servicesfile.close();
    this->loadServices();
}

/**
 * Remove a service from the upcoming services and add it to finished services
 * @param service
 */
void Airline::addToFinishedServices(Service* service) {
    string plate = service->getPlanePlate();
    for(auto & plane : planes){
        if(plane->getRegistrationPlate() == plate) plane->dequeueService(service);
    }
    removeAllServices();
    storeAllServices();
}

/**
 * Add a service to the upcoming services queue
 * @param service
 */
void Airline::addToUpcomingServices(Service* service) {
    string plate = service->getPlanePlate();
    for(auto & plane : planes){
        if(plane->getRegistrationPlate() == plate) plane->queueService(service);
    }
}

void Airline::showUpcomingServices(const string& plate) {
    for(Plane* plane : planes) if (plane->getRegistrationPlate() == plate) plane->showUpcomingServices();
}

void Airline::showFinishedServices(const string& plate) {
    for(Plane* plane : planes) if (plane->getRegistrationPlate() == plate) plane->showFinishedServices();
}

/**
 * Remove all flights that depended on a removed airport
 * @param airportName
 */
void Airline::removeFlights(const string &airportName) {
    for(int i = 0; i < flights.size(); i++ ){
        if(flights[i]->getOrigin()->getName() == airportName || flights[i]->getDestination()->getName() == airportName){
            //delete flights[i];
            //flights[i] = nullptr;
            flights.erase(flights.begin()+i);
            --i;
        }
    }
}

//Remove all tickets dependent on a flight that depended on a removed airport
void Airline::removeTickets(const string &airport_name) {
    for(int i = 0; i < flights.size(); i++ ){
        if(flights[i]->getOrigin()->getName() == airport_name || flights[i]->getDestination()->getName() == airport_name){
            for(int idx = 0 ; idx < tickets.size() ; idx ++){
                if(tickets[idx]->getFlightId() == flights[i]->getNumber()){
                    //delete tickets[idx];
                    //tickets[idx] = nullptr;
                    tickets.erase(tickets.begin() + idx);
                    --idx;
                }
            }
        }
    }
}

/**
 * Remove all tickets that belonged to a removed flight
 * @param id
 */
void Airline::removeTickets(const int &id) {
    for(int idx = 0 ; idx < tickets.size() ; idx ++){
        if(tickets[idx]->getFlightId() == id){
            //delete tickets[idx];
            //tickets[idx] = nullptr;
            tickets.erase(tickets.begin() + idx);
            --idx;
        }
    }
}

/**
 * Remove flights and ticktes that depended on a removed plane
 * @param plate
 */
void Airline::removeFlightsofPlaneandTickets(const string & plate) {
    for(int i = 0 ; i< flights.size() ; i++){
        if(flights[i]->getPlanePlate() == plate){
            removeTickets(flights[i]->getNumber());
            //delete flights[i];
            //flights[i] = nullptr;
            flights.erase(flights.begin() + i);
            --i;
        }
    }
}
