#include "menu.h"
#include "AuxiliaryFunctions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

void Menu::mainMenu() {

    this->airline = Airline();
    this->load(); //Loads everything from a text file

    std::string option;

    // Ask for a valid input
    while (true) {

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "|         Welcome to Travel Code Airlines        |" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "1. Client" << std::endl;
        std::cout << "2. Management" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool stop = parseInput(2,option);
        if (stop) break;
    }
    switch (std::stoi(option)) {

        case 1:
            clientMenu();
            break;

        case 2:
            adminMenu();
            break;

        case 0:
            exitMenu();
    }
}

void Menu::clientMenu() {
    std::string option;
    // Ask for a valid input
    while (true) {
        std::cout << "Path: Client" << std::endl;
        std::cout << "1. Buy Tickets" << std::endl;
        std::cout << "2. Means of transport" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(2,option);
        if (correct){
            switch(std::stoi(option)) {
                case 1:
                    buyTicketsMenu();
                    break;
                case 2:
                    clientTransportsMenu();
                    break;
                case 0:
                    exitMenu();
                    break;
            }
        }
    }
}

void Menu::buyTicketsMenu(){
    std::cout << "Path: Client\\Buy Tickets" << std::endl;
    airline.newPassengers();
}

void Menu::clientTransportsMenu() {
    std::cout << "Path: Client\\Means of transport" << std::endl;
    airline.searchMeansOfTransport();
}

void Menu::adminMenu() {
    std::string option;

    // Ask for a valid input
    while (true) {
        std::cout << "Path: Management" << std::endl;
        std::cout << "1. Planes" << std::endl;
        std::cout << "2. Airports" << std::endl;
        std::cout << "3. Transports" << std::endl;
        std::cout << "4. Workers" << std::endl;
        std::cout << "5. Passengers" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(5,option);
        if (correct){
            switch(std::stoi(option)) {
                case 1:
                    planesMenu();
                    break;
                case 2:
                    airportsMenu();
                    break;
                case 3:
                    transportsMenu();
                    break;
                case 4:
                    workersMenu();
                    break;
                case 5:
                    passengersMenu();
                    break;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::planesMenu() {
    std::string option;

    // Ask for a valid input
    while (true) {
        std::cout << "Path: Management\\Planes" << std::endl;
        std::cout << "1. Manage vehicles" << std::endl;
        std::cout << "2. Manage services" << std::endl;
        std::cout << "3. Manage flights" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(4,option);
        if (correct){
            switch(std::stoi(option)) {
                case 1:
                    planesManagementMenu();
                    break;
                case 2:
                    servicesManagementMenu();
                    break;
                case 3:
                    flightsManagementMenu();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::planesManagementMenu(){
    std::string option;

    while (true) {
        std::cout << "Path: Management\\Planes\\Manage vehicles" << std::endl;
        std::cout << "1. Add a plane" << std::endl;
        std::cout << "2. Remove a plane" << std::endl;
        std::cout << "3. Show planes" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    addPlanesMenu();
                    break;
                case 2:
                    removePlanesMenu();
                    break;
                case 3:
                    showPlanesMenu();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::addPlanesMenu(){

    string nr_planes;

    while(true){
        std::cout << "How many planes do you wish to add (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_planes);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_planes)) {
            if (std::stoi(nr_planes) >= 0) {
                switch (std::stoi(nr_planes)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_planes); i++)
                            askForPlane(i);
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }

}

void Menu::removePlanesMenu() {
    string nr_planes;

    while(true){
        std::cout << "How many planes do you wish to remove (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_planes);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_planes)) {
            if (std::stoi(nr_planes) >= 0) {
                switch (std::stoi(nr_planes)) {
                    default: {
                        string plate;
                        for(int i = 1; i <= std::stoi(nr_planes);){
                            std::cout << "Enter Plane " << i << "'s registration plate: " << std::endl;
                            std::getline(std::cin, plate);
                            if(!airline.removePlanes(plate)){
                                std::cout << "Plane doesn't exist!" << std::endl;
                                --i;
                            }
                            i++;
                        }
                        return;
                    }
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }

}

void Menu::showPlanesMenu() {
    while (true) {
        std::string option;
        std::cout << R"(Path: Management\Planes\Manage vehicles\Show planes)" << std::endl;
        std::cout << "1: Show Planes by registration plate" << std::endl;
        std::cout << "2: Show Planes by type" << std::endl;
        std::cout << "3: Show Planes by capacity" << std::endl;
        std::cout << "4: Back" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    airline.showPlanesByCriteria("plate");
                    break;
                case 2:
                    airline.showPlanesByCriteria("type");
                    break;
                case 3:
                    airline.showPlanesByCriteria("capacity");
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::servicesManagementMenu() {

    std::string option;

    while (true) {
        std::cout << "Path: Management\\Planes\\Manage services" << std::endl;
        std::cout << "1. Add a service" << std::endl;
        std::cout << "2. Remove a service" << std::endl;
        std::cout << "3. Show services" << std::endl;
        std::cout << "4. Update services" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(5,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    addServicesMenu();
                    break;
                case 2:
                    removeServicesMenu();
                    break;
                case 3:
                    showServicesMenu();
                    break;
                case 4:
                    updateServicesMenu();
                    break;
                case 5:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}
/**
 * Ask for a plane to add services to
 */
void Menu::addServicesMenu() {

    string plate;

    while(true){
        std::cout << "Specify a plane's registration plate to which you wish to add services to (type 0 to go back): ";

        std::getline(std::cin, plate);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(plate)){
            if (std::stoi(plate) == 0) return;
        }
        if(airline.planeExists(plate)){
            break;
        }
        std::cout << "Plane doesn't exist." << std::endl;
    }
    Service* service = askForService(plate);
    airline.addService(service);
    airline.addToUpcomingServices(service);
}

/**
 * Ask for a plane to remove upcoming services
 */
void Menu::removeServicesMenu() {

    std::string plate;

    while(true){
        std::cout << "You can only remove upcoming services!" << std::endl;
        std::cout << "Specify a plane's registration plate to which you wish to remove services from (type 0 to go back): ";

        std::getline(std::cin, plate);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(plate)){
            if (std::stoi(plate) == 0) return;
        }
        if(airline.planeExists(plate)){
            break;
        }
        std::cout << "Plane doesn't exist." << std::endl;
    }
    if(!airline.removeService(askForService(plate))){
        std::cout << "Service doesn't exist!" << std::endl;
    }
    else{cout << "Service was removed successfully" << endl;}

}

/**
 * Ask for a plane to update a service
 */
void Menu::updateServicesMenu(){
    string plate;

    while(true){
        std::cout << "Specify a plane's registration plate to which you wish to update services (type 0 to go back): ";

        std::getline(std::cin, plate);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(plate)){
            if (std::stoi(plate) == 0) return;
        }
        if(airline.planeExists(plate)){
            break;
        }
        std::cout << "Plane doesn't exist." << std::endl;
    }
    Service* service = askForService(plate);
    airline.addToFinishedServices(service);
    std::cout << "Service Updated" << std::endl;
}
//TODO
/**
 * Choose which services to see and from what plane
 */
void Menu::showServicesMenu() {
    std::string option;

    while (true) {
        std::cout << R"(Path: Management\Planes\Manage services\Show services)" << std::endl;
        std::cout << "1. Show all services" << std::endl;
        std::cout << "2. Show upcoming services from a plane" << std::endl;
        std::cout << "3. Show finished services from a plane" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";
        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if (correct) {
            switch (std::stoi(option)) {
                case 1:
                    airline.showServices();
                    break;
                case 2:{
                    string plate;

                    while(true){
                        std::cout << "Specify a plane's registration plate to which you wish to see upcoming services (type 0 to go back): ";

                        std::getline(std::cin, plate);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        if(isAllDigits(plate)){
                            if (std::stoi(plate) == 0) return;
                        }
                        if(airline.planeExists(plate)){
                            break;
                        }
                        std::cout << "Plane doesn't exist." << std::endl;
                    }
                    airline.showUpcomingServices(plate);
                    break;
                }
                case 3:{
                    string plate;

                    while(true){
                        std::cout << "Specify a plane's registration plate to which you wish to see finished services (type 0 to go back): ";

                        std::getline(std::cin, plate);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        if(isAllDigits(plate)){
                            if (std::stoi(plate) == 0) return;
                        }
                        if(airline.planeExists(plate)){
                            break;
                        }
                        std::cout << "Plane doesn't exist." << std::endl;
                    }
                    airline.showFinishedServices(plate);
                    break;
                }
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::flightsManagementMenu() {
    std::string option;

    while (true) {
        std::cout << "Path: Management\\Planes\\Manage flights" << std::endl;
        std::cout << "1. Add a flight" << std::endl;
        std::cout << "2. Remove a flight" << std::endl;
        std::cout << "3. Show flights" << std::endl;
        std::cout << "4. Update flights" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";
        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(5,option);
        if (correct) {
            switch (std::stoi(option)) {
                case 1:
                    addFlightsMenu();
                    break;
                case 2:
                    removeFlightsMenu();
                    break;
                case 3:
                    showFlightsMenu();
                    break;
                case 4:
                    updateFlightsMenu();
                    break;
                case 5:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::addFlightsMenu() {
    std::string nr_flights;
    while(true){
        std::cout << "How many Flights do you wish to add (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_flights);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_flights)) {
            if (std::stoi(nr_flights) >= 0) {
                switch (std::stoi(nr_flights)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_flights); i++)
                            askForFlight(i);
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::removeFlightsMenu() {
    std::string nr_flights, departure, arrival, year, month, day;
    bool validDate = false;
    while(true){
        std::cout << "How many flights do you wish to remove (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_flights);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_flights)) {
            if (std::stoi(nr_flights) >= 0) {
                switch (std::stoi(nr_flights)) {
                    default: {
                        string plate;
                        for(int i = 1; i <= std::stoi(nr_flights);){
                            std::cout << "Flight " << i << endl;
                            std::cout << "Departure Airport:";
                            std::getline(std::cin, departure);
                            if (std::cin.eof()) {
                                exitMenu();
                            }
                            std::cout << "Arrival Airport:";
                            std::getline(std::cin, arrival);
                            if (std::cin.eof()) {
                                exitMenu();
                            }

                            std::cout << "Plane Plate:";
                            std::getline(std::cin, plate);
                            if (std::cin.eof()) {
                                exitMenu();
                            }

                            Plane *plane2 = airline.getPlane(plate);

                            time_t theTime = time(nullptr);
                            struct tm *aTime = localtime(&theTime);

                            int dayNow = aTime->tm_mday;
                            int monthNow = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
                            int yearNow = aTime->tm_year + 1900; // Year is # years since 1900

                            while(!validDate) {

                                while (true) {
                                    std::cout << "Year:";
                                    std::getline(std::cin, year);
                                    if (std::cin.eof()) {
                                        exitMenu();
                                    }
                                    if (isAllDigits(year)) {
                                        if (std::stoi(year) > 2020) {
                                            break;
                                        } else {
                                            std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                                        }
                                    } else {
                                        std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                                    }
                                }

                                while (true) {
                                    std::cout << "Month:";
                                    std::getline(std::cin, month);
                                    if (std::cin.eof()) {
                                        exitMenu();
                                    }
                                    if (isAllDigits(month)) {
                                        if (std::stoi(month) <= 12 && std::stoi(month) > 0) {
                                            break;
                                        } else {
                                            std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                                        }
                                    } else {
                                        std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                                    }
                                }
                                if (stoi(month) < 10) {
                                    month = "0" + month;
                                }

                                while(true) {
                                    std::cout << "Day:";
                                    std::getline(std::cin, day);
                                    if (std::cin.eof()) {
                                        exitMenu();
                                    }
                                    if (isAllDigits(day)) {
                                        //Leap year month 2
                                        if ((std::stoi(year) % 4 == 0 && (std::stoi(year) % 100 != 0 || std::stoi(year) % 400 == 0)) && std::stoi(month) == 2 && std::stoi(day) < 30 && std::stoi(day) > 0) break;

                                            //Not leap year month 2
                                        else if (std::stoi(month) == 2 && std::stoi(day) < 29 && std::stoi(day) > 0) break;

                                        else if (std::stoi(day) < 32 && std::stoi(day) > 0) break;

                                        else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;
                                    }
                                    else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;

                                }

                                if (stoi(day) < 10) {
                                    day = "0" + day;
                                }
                                Date d1 = Date(stoi(year), stoi(month), stoi(day));
                                validDate = checkDate(d1);
                                if (!validDate) cout << std::endl << "Not a valid Date!" << std::endl;
                                }
                            if(!airline.removeFlight(departure,arrival,plate,Date(stoi(year),stoi(month),stoi(day)))){
                                std::cout << "Flight doesn't exist!" << std::endl;
                                --i;
                            }
                            else{cout << "The flight was removed successfully" << endl;}
                            i++;
                        }
                        return;
                    }
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }

}

/**
 * Show flights with some possible filters and show the occupation of the transport car of a flight
 */
void Menu::showFlightsMenu() {
    while (true) {
        std::string option;
        std::cout << R"(Path: Management\Planes\Manage flights\Show flights)" << std::endl;
        std::cout << "1. Show all flights from database" << std::endl;
        std::cout << "2. Show all flights from one or multiple planes" << std::endl;
        std::cout << "3. Show all flights from/to one or multiple cities" << std::endl;
        std::cout << "4. Show the occupation of the transport car of a flight" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(5,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    airline.showFlights();
                    break;
                case 2: {
                    vector<string> plates;
                    while(true){
                        string plate;
                        std::cout << "Specify a plane's registration plate to which you wish to see the flights from (type 0 to go back or 1 to stop adding plates): " << std::endl;

                        std::getline(std::cin, plate);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        if(isAllDigits(plate)){
                            if (std::stoi(plate) == 0) return;
                            if(std::stoi(plate) == 1) break;
                        }
                        if(airline.planeExists(plate)){
                            plates.push_back(plate);
                        }
                        else std::cout << "Plane doesn't exist. Specify an existing one." << std::endl;
                    }
                    airline.showFlightsByPlate(plates);
                    break;
                }
                case 3: {
                    vector<string> cities;
                    bool arriving;
                    string option2;
                    while(true){

                        std::cout << "Do you wish to see arriving or departing flights?" << std::endl;
                        std::cout << "1. Arriving" << std::endl;
                        std::cout << "2. Departing" << std::endl;
                        std::cout << "Choose an option from the above: ";

                        std::getline(std::cin, option2);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        bool fine = parseInput(2,option2);
                        if(fine){
                            arriving = (std::stoi(option2) == 1);
                            break;
                        }
                    }
                    while(true){
                        string city;
                        std::cout << "Specify a city to which you want to see the flights that" << (arriving ? " arrive in it" : " depart from it") << "(type 0 to go back or 1 to stop adding plates): " << std::endl;

                        std::getline(std::cin, city);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        if(isAllDigits(city)){
                            if (std::stoi(city) == 0) return;
                            if(std::stoi(city) == 1) break;
                        }
                        if(arriving){
                            if(airline.arrivalCityExists(city)){
                                cities.push_back(city);
                            }
                            else std::cout << "City doesn't exist." << std::endl;
                        }
                        else{
                            if(airline.departureCityExists(city)){
                                cities.push_back(city);
                            }
                            else std::cout << "City doesn't exist." << std::endl;
                        }
                    }
                    if(arriving) airline.showFlightsByArrival(cities);
                    else airline.showFlightsByDeparture(cities);
                    break;
                }
                case 4: {
                    Flight *chosen_flight = airline.chooseFlight();
                    chosen_flight->showCar();
                }
                case 5:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

/**
 * Update attributes of a flight if it exists
 */
void Menu::updateFlightsMenu() {

    std::string flight_number, new_arrival, new_year, new_month, new_day, new_time_str, year, day, month;
    bool validDate = false;
    while(true){
        airline.showFlights();
        std::cout << "Which flight would you like to update? (Type 0 if you wish to exit): ";
        std::getline(std::cin, flight_number);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(flight_number) && std::stoi(flight_number) >= 0 ) {
            auto chosen_flight = airline.getFlightById(stoi(flight_number));
            if (*chosen_flight == *(new Flight(new Airport(), new Airport()))) {
                std::cout << "Could not find the desired flight." << std::endl << std::endl;
                delete chosen_flight;
                return;
            }
            switch (std::stoi(flight_number)) {
                default: {
                    std::cout << "Choose one option to update: 'Destination', 'Date', 'Time': ";
                    std::string option;
                    std::getline(std::cin, option);
                    while(option != "Destination" && option != "Date" && option != "Time"){
                        std::cout << "Invalid. Please choose one option to update: 'Destination', 'Date', 'Time': ";
                        std::getline(std::cin, option);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                    }

                    if (option == "Destination") {
                        std::cout << "New Arrival Airport:";
                        std::getline(std::cin, new_arrival);
                        if (std::cin.eof()) {
                            exitMenu();
                        }
                        bool destination_updated = airline.updateFlightDestination(std::stoi(flight_number), new_arrival);
                        if(!destination_updated){
                            return;
                        }


                    }

                    else if(option == "Time"){
                        std::cout << "New Time ('HH:MM'):";
                        bool vTime = false;
                        while(!vTime){
                            std::cout << "Time (HH:MM): ";
                            std::getline(std::cin, new_time_str);
                            vTime = validateTime(new_time_str);
                            if (std::cin.eof()) {
                                exitMenu();
                            }
                            else {
                                std::cout << "Please enter a valid time: ";
                            }
                        }
                        Time_m new_time(new_time_str);
                        bool valid_time = new_time.validTime();
                        while(!valid_time){
                            std::cout << "Not valid. New Time ('HH:MM'):";
                            std::getline(std::cin, new_time_str);
                            if (std::cin.eof()) {
                                exitMenu();
                            }
                            new_time = Time_m(new_time_str);
                            valid_time = new_time.validTime();
                        }
                        airline.updateFlightTime(stoi(flight_number), new_time);

                    }

                    else if(option == "Date") {

                        time_t theTime = time(nullptr);
                        struct tm *aTime = localtime(&theTime);

                        int dayNow = aTime->tm_mday;
                        int monthNow = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
                        int yearNow = aTime->tm_year + 1900; // Year is # years since 1900

                        while (!validDate) {

                            while (true) {
                                std::cout << "New Year:";
                                std::getline(std::cin, year);
                                if (std::cin.eof()) {
                                    exitMenu();
                                }
                                if (isAllDigits(year)) {
                                    if (std::stoi(year) > 2020) {
                                        break;
                                    } else {
                                        std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                                    }
                                } else {
                                    std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                                }
                            }

                            while (true) {
                                std::cout << "New Month:";
                                std::getline(std::cin, month);
                                if (std::cin.eof()) {
                                    exitMenu();
                                }
                                if (isAllDigits(month)) {
                                    if (std::stoi(month) <= 12 && std::stoi(month) > 0) {
                                        break;
                                    } else {
                                        std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                                    }
                                } else {
                                    std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                                }
                            }
                            if (stoi(month) < 10) {
                                month = "0" + month;
                            }

                            while(true) {
                                std::cout << "New day:";
                                std::getline(std::cin, day);
                                if (std::cin.eof()) {
                                    exitMenu();
                                }
                                if (isAllDigits(day)) {
                                    //Leap year month 2
                                    if ((std::stoi(year) % 4 == 0 && (std::stoi(year) % 100 != 0 || std::stoi(year) % 400 == 0)) && std::stoi(month) == 2 && std::stoi(day) < 30 && std::stoi(day) > 0) break;

                                        //Not leap year month 2
                                    else if (std::stoi(month) == 2 && std::stoi(day) < 29 && std::stoi(day) > 0) break;

                                    else if (std::stoi(day) < 32 && std::stoi(day) > 0) break;

                                    else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;
                                }
                                else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;

                            }
                            if (stoi(day) < 10) {
                                day = "0" + day;
                            }
                            Date d1 = Date(stoi(year), stoi(month), stoi(day));
                            validDate = checkDate(d1);
                            if (!validDate) cout << std::endl << "Not a valid Date!" << std::endl;
                        }
                        Date new_date(stoi(year), stoi(month), stoi(day));
                        airline.updateFlightDate(stoi(flight_number), new_date);

                    }
                    airline.updateFlight();
                std::cout << "The flight was updated successfully" << endl;
                return;
                }
                case 0:
                    return;
            }
        }
        else std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
    }
}

void Menu::airportsMenu(){
    std::string option;
    std::string name, city, country;
    while (true) {
        std::cout << "Path: Management\\Airports" << std::endl;
        std::cout << "1. Add an airport" << std::endl;
        std::cout << "2. Remove an airport" << std::endl;
        std::cout << "3. Show airports" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    addAirportsMenu();
                    break;
                case 2:
                    removeAirportsMenu();
                    break;

                case 3:
                    showAirportsMenu();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::addAirportsMenu(){
    string nr_airports;

    while(true){
        std::cout << "How many airports do you wish to add (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_airports);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_airports)) {
            if (std::stoi(nr_airports) >= 0) {
                switch (std::stoi(nr_airports)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_airports); i++)
                            askForAirport(i);
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::removeAirportsMenu() {
    string nr_airports;

    while(true){
        std::cout << "How many airports do you wish to remove (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_airports);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_airports)) {
            if (std::stoi(nr_airports) >= 0) {
                switch (std::stoi(nr_airports)) {
                    default: {
                        string name;
                        for(int i = 1; i <= std::stoi(nr_airports);){
                            std::cout << "Enter Airport " << i << "'s name: " << std::endl;
                            std::getline(std::cin, name);
                            if(!airline.removeAirport(name)){
                                std::cout << "Could not find specified airport!" << std::endl;
                                --i;
                            }
                            i++;
                        }
                        return;
                    }
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::showAirportsMenu(){
    while (true) {
        std::string option;
        std::cout << "Path: Management\\Airports\\Show airports" << std::endl;
        std::cout << "1: Show all Airports from database" << std::endl;
        std::cout << "2: Show all Airports from one or multiple cities" << std::endl;
        std::cout << "3: Show all Airports from one or multiple countries" << std::endl;
        std::cout << "4: Back" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    airline.showAirports();
                    break;
                case 2: {
                    set<string> cities;
                    string city;
                    while(true){
                        std::cout << "Specify a city you wish to see the airports from(type 0 to go back or 1 to stop): " << std::endl;
                        std::getline(std::cin, city);
                        if(isAllDigits(city)){
                            if(std::stoi(city) == 0) return;
                            if(std::stoi(city) == 1) break;
                        }
                        if(airline.getCities().count(city)) cities.insert(city);
                        else {std::cout << "There are no airports in that city" << std::endl;}
                    }
                    vector<string> citiesv {cities.begin(), cities.end()};
                    airline.showAirportByCity(citiesv);
                    break;
                }
                case 3: {
                    set<string> countries;
                    string country;
                    while(true){
                        std::cout << "Specify a country you wish to see the airports from(type 0 to go back or 1 to stop): " << std::endl;
                        std::getline(std::cin, country);
                        if(isAllDigits(country)){
                            if(std::stoi(country) == 0) return;
                            if(std::stoi(country) == 1) break;
                        }
                        if(airline.getCountries().count(country)) countries.insert(country);
                        else {std::cout << "There are no airports in that country" << std::endl;}
                    }
                    vector<string> countriesv {countries.begin(), countries.end()};
                    airline.showAirportByCountry(countriesv);
                    break;
                }
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::transportsMenu() {

    std::string option;

    while (true) {
        std::cout << "Path: Management\\Transports" << std::endl;
        std::cout << "1. Add a transport" << std::endl;
        std::cout << "2. Remove a transport" << std::endl;
        std::cout << "3. Show means of transport" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    addTransportsMenu();
                    break;
                case 2:
                    removeTransportsMenu();
                    break;
                case 3:
                    showTransportsMenu();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::addTransportsMenu() {
    std::string nr_transports, airport_name;
    std::cout << "Specify which Airport you would like to add Transports:" << std::endl;
    std::getline(std::cin, airport_name);
    if (std::cin.eof()) {
        exitMenu();
    }
    while(!airline.airportExists(airport_name)){
        std::cout << "Airport does not exist. Try Again!" << endl;
        std::cout << "Specify which Airport you would like to add Transports:" << std::endl;
        std::getline(std::cin, airport_name);
    }
    while(true){
        std::cout << "How many transports do you wish to add to this airport (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_transports);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_transports)) {
            if (std::stoi(nr_transports) >= 0) {
                switch (std::stoi(nr_transports)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_transports); i++){
                            Airport* airport = airline.getAirport(airport_name);
                            askForTransport(i,airport);
                        }
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::removeTransportsMenu() {
    std::string nr_transports, airport_name,type;
    bool hasT = false;
    Airport* airport;
    while(!hasT){
        std::cout << "Specify which Airport you would like to remove transports:" << std::endl;
        std::getline(std::cin, airport_name);
        if (std::cin.eof()) {
            exitMenu();
        }
        while(!airline.airportExists(airport_name)){
            std::cout << "Airport does not exist. Try Again!" << endl;
            std::cout << "Specify which Airport you would like to remove transports:" << std::endl;
            std::getline(std::cin, airport_name);
        }
        airport = airline.getAirport(airport_name);
        if(!airport->hasTransport("bus") && !airport->hasTransport("metro") && !airport->hasTransport("train"))
            std::cout << "Selected Airport does not have transports. Try Again!" << endl;
        else hasT = true;
    }
    while(true){
        std::cout << "How many transports do you wish to remove to this airport (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_transports);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_transports)) {
            if (std::stoi(nr_transports) >= 0) {
                switch (std::stoi(nr_transports)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_transports); i++){
                            airport = airline.getAirport(airport_name);
                            while(true){
                                std::cout << "Type of Transport(bus, metro or train):";
                                std::getline(std::cin, type);
                                if (std::cin.eof()) {
                                    exitMenu();
                                }
                                while(type != "bus" && type != "metro" && type != "train"){
                                    std::cout << "Invalid Transport. Try Again!" << endl;
                                    std::cout << "Type of Transport(bus, metro or train):";
                                    std::getline(std::cin, type);
                                }
                                if(!(*airport).hasTransport(type)){
                                    cout << "Airport does not have that type of transport"<< endl;
                                }
                                else {
                                    cout << "Transport has been removed!" << endl;
                                    break;
                                }
                            }
                            airport->removeTransport(type);
                            airline.removeAllTransports();
                            airline.storeAllTransports();
                            airline.loadTransports();
                        }
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::showTransportsMenu(){
    airline.searchMeansOfTransport();
}

void Menu::workersMenu() {
    std::string option;

    while (true) {
        std::cout << "Path: Management\\Workers" << std::endl;
        std::cout << "1. Add a worker" << std::endl;
        std::cout << "2. Remove a worker" << std::endl;
        std::cout << "3. Show workers" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    addWorkersMenu();
                    break;
                case 2:
                    removeWorkersMenu();
                    break;
                case 3:
                    showWorkersMenu();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

void Menu::addWorkersMenu() {
    std::string nr_workers;
    while(true){
        std::cout << "How many workers do you wish to add (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_workers);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_workers)) {
            if (std::stoi(nr_workers) >= 0) {
                switch (std::stoi(nr_workers)) {
                    default:
                        for(int i = 1; i <= std::stoi(nr_workers); i++)
                            askForWorker(i);
                        return;
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::removeWorkersMenu() {
    string nr_workers;

    while(true){
        std::cout << "How many workers do you wish to remove (Type 0 if you wish to exit): ";
        std::getline(std::cin, nr_workers);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(nr_workers)) {
            if (std::stoi(nr_workers) >= 0) {
                switch (std::stoi(nr_workers)) {
                    default: {
                        string id;
                        for(int i = 1; i <= std::stoi(nr_workers);){
                            std::cout << "Enter worker " << i <<  " id: " << std::endl;
                            std::getline(std::cin, id);
                            while(!isAllDigits(id)){
                                std::cout << "Please enter a valid id: "<< std::endl;
                                std::getline(std::cin, id);
                            }
                            if(!airline.removeWorker(stoi(id))){
                                std::cout << "Could not find specified worker!" << std::endl;
                                --i;
                            }
                            i++;
                        }
                        return;
                    }
                    case 0:
                        return;
                }
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

void Menu::showWorkersMenu() {
    while (true) {
        std::string option;
        std::cout << "Path: Management\\Workers\\Show workers" << std::endl;
        std::cout << "1. Show all Workers from database" << std::endl;
        std::cout << "2. Show all Workers in alphabetical order" << std::endl;
        std::cout << "3. Show all Workers in reverse alphabetical order" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    airline.showWorkers();
                    break;
                case 2:
                    airline.showWorkersAZ();
                    break;
                case 3:
                    airline.showWorkersZA();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}
void Menu::passengersMenu() {
    std::string option;

    while (true) {
        std::cout << R"(Path: Management\\Passengers)" << std::endl;
        std::cout << "1. Show passengers" << std::endl;
        std::cout << "2. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }

        bool correct = parseInput(2,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    showPassengersMenu();
                    break;
                case 2:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}
void Menu::showPassengersMenu(){
    while (true) {
        std::string option;
        std::cout << "Path: Management\\Passengers\\Show passengers" << std::endl;
        std::cout << "1. Show all Passengers from database" << std::endl;
        std::cout << "2. Show all Passengers of a flight in alphabetical order" << std::endl;
        std::cout << "3. Show all Passengers of a flight in reverse alphabetical order" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if (correct) {
            switch(std::stoi(option)) {
                case 1:
                    airline.showPassengers();
                    break;
                case 2:
                    airline.showPassengersByFlightAZ();
                    break;
                case 3:
                    airline.showPassengersByFlightZA();
                    break;
                case 4:
                    return;
                case 0:
                    exitMenu();
            }
        }
    }
}

/**
 * Ssk the info of a plane to add to the airline
 * @param i
 */
void Menu::askForPlane(int i){
    string plate, type, capacity, cols;

    std::cout << "Plane " << i << std::endl;
    std::cout << "Specify the attributes of the plane you wish to add" << std::endl;
    while(true){

        std::cout << "Registration plate (Type 0 to go back): ";
        std::getline(std::cin, plate);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(plate)){
            if (std::stoi(plate) == 0) return;
        }
        if(!airline.planeExists(plate)){
           break;
        }
        std::cout << "Plane already exists. Specify a new one or remove existing one!" << std::endl;
    }

    std::cout << "Plane type: ";
    std::getline(std::cin, type);
    if (std::cin.eof()) {
        exitMenu();
    }

    while(true){
        std::cout << "Total capacity: ";
        std::getline(std::cin, capacity);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(capacity)) {
            if (std::stoi(capacity) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }

    while(true){
        std::cout << "Number of columns: ";
        std::getline(std::cin, cols);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(cols)) {
            if (std::stoi(cols) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
    airline.addPlanes(new Plane(plate, type, std::stoi(capacity), std::stoi(cols)));
}

/**
 * Ask for the info of a service to add to the given plane
 * @param plate
 * @return
 */
Service* Menu::askForService(const string& plate){
    std::string type, year, month, day, worker_id;
    bool validDate = false;
    Date d1;

    std::cout << "Specify the attributes of the service you wish to add" << std::endl;
    std::cout << "Scheduled date: " << std::endl;
    while(!validDate){

        while(true){
            std::cout << "Year: ";
            std::getline(std::cin, year);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(year)) {
                if (std::stoi(year) > 2020) {
                    break;
                } else {
                    std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                }
            } else {
                std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
            }
        }

        while(true){
            std::cout << "Month: ";
            std::getline(std::cin, month);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(month)) {
                if (std::stoi(month) <= 12 && std::stoi(month) > 0) {
                    break;
                } else {
                    std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                }
            } else {
                std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
            }
        }
        if(stoi(month)<10) {
            month = "0" + month;
        }

        while(true) {
            std::cout << "Day:";
            std::getline(std::cin, day);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(day)) {
                //Leap year month 2
                if ((std::stoi(year) % 4 == 0 && (std::stoi(year) % 100 != 0 || std::stoi(year) % 400 == 0)) && std::stoi(month) == 2 && std::stoi(day) < 30 && std::stoi(day) > 0) break;

                //Not leap year month 2
                else if (std::stoi(month) == 2 && std::stoi(day) < 29 && std::stoi(day) > 0) break;

                else if (std::stoi(day) < 32 && std::stoi(day) > 0) break;

                else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;
            }
            else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;

        }

        if(stoi(day)<10) {
            day = "0" + day;
        }
        d1 = Date(stoi(year),stoi(month),stoi(day));
        validDate = checkDate(d1);
        if(!validDate) cout << std::endl << "Not a valid Date!" << std::endl;
    }

    while(true){
        std::cout<<"Specify the ID of the worker that will fulfill the service: ";
        std::getline(std::cin, worker_id);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(worker_id)) {
            if (airline.workerExists(std::stoi(worker_id))) {
                break;
            } else {
                std::cerr << std::endl << "Worker ID doesn't exist!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid ID!" << std::endl << std::endl;
        }
    }

    string option;
    while (true) {
        std::cout << "Specify the type of service" << std::endl;
        std::cout << "1. Cleaning" << std::endl;
        std::cout << "2. Maintenance" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";
        std::getline(std::cin, option);
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(2,option);
        if (correct) break;
    }
    switch (std::stoi(option)) {
        case 1:
            type = "cleaning";
            break;
        case 2:
            type = "maintenance";
            break;
        case 0:
            exitMenu();
    }
    auto service = new Service(plate, d1, stoi(worker_id), type, false);
    return service;
}

/**
 * Ask for the info of a flight to add
 * @param i
 */
void Menu::askForFlight(int i){
    std::string departure, arrival, plate, year, month, day, duration, time_str, car_c, car_n, car_m;
    bool validDate = false, validPlane = false;
    std::cout << "Flight " << i << std::endl;
    std::cout << "Specify the attributes of the flight you wish to add" << std::endl;
    std::cout << "Departure Airport:";
    std::getline(std::cin, departure);
    if (std::cin.eof()) {
        exitMenu();
    }
    while(!airline.airportExists(departure)){
        std::cout << "Airport does not exist. Try Again!" << endl;
        std::cout << "Departure Airport:";
        std::getline(std::cin, departure);
    }

    std::cout << "Arrival Airport:";
    std::getline(std::cin, arrival);
    if (std::cin.eof()) {
        exitMenu();
    }
    while(!airline.airportExists(arrival)){
        std::cout << "Airport does not exist. Try Again!" << endl;
        std::cout << "Arrival Airport:";
        std::getline(std::cin, arrival);
    }

    std::cout << "Plane Plate:";
    std::getline(std::cin, plate);
    if (std::cin.eof()) {
        exitMenu();
    }
    while(!airline.planeExists(plate)){
        std::cout << "Plane does not exist. Try Again!" << endl;
        std::cout << "Plane Plate:";
        std::getline(std::cin, plate);
    }
    Plane *plane2 = airline.getPlane(plate);

    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);

    int dayNow = aTime->tm_mday;
    int monthNow = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int yearNow = aTime->tm_year + 1900; // Year is # years since 1900

    while(!validDate || !validPlane){

        while(true){
            std::cout << "Year:";
            std::getline(std::cin, year);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(year)) {
                if (std::stoi(year) > 2020) {
                    break;
                } else {
                    std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
                }
            } else {
                std::cerr << std::endl << "Not a valid Year!" << std::endl << std::endl;
            }
        }

        while(true){
            std::cout << "Month:";
            std::getline(std::cin, month);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(month)) {
                if (std::stoi(month) <= 12 && std::stoi(month) > 0) {
                    break;
                } else {
                    std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
                }
            } else {
                std::cerr << std::endl << "Not a valid Month!" << std::endl << std::endl;
            }
        }
        if(stoi(month)<10) {
            month = "0" + month;
        }

        while(true) {
            std::cout << "Day:";
            std::getline(std::cin, day);
            if (std::cin.eof()) {
                exitMenu();
            }
            if (isAllDigits(day)) {
                //Leap year month 2
                if ((std::stoi(year) % 4 == 0 && (std::stoi(year) % 100 != 0 || std::stoi(year) % 400 == 0)) && std::stoi(month) == 2 && std::stoi(day) < 30 && std::stoi(day) > 0) break;

                //Not leap year month 2
                else if (std::stoi(month) == 2 && std::stoi(day) < 29 && std::stoi(day) > 0) break;

                else if (std::stoi(day) < 32 && std::stoi(day) > 0) break;

                else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;
            }
            else std::cerr << std::endl << "Not a valid Day!" << std::endl << std::endl;

        }
        if(stoi(day)<10) {
            day = "0" + day;
        }
        Date d1 = Date(stoi(year),stoi(month),stoi(day));
        validDate = checkDate(d1);
        if(!validDate) cout << std::endl << "Not a valid Date!" << std::endl;
        validPlane = checkForPlaneAvailability(d1,*plane2);
        if(!validPlane && validDate) std::cerr << std::endl << "Plane already has a flight at this Date!" << std::endl << std::endl;


    }

    while(true){
        std::cout << "Duration:";
        std::getline(std::cin, duration);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(duration)) {
            if (std::stoi(duration) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid Duration!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid Duration!" << std::endl << std::endl;
        }
    }
    bool vTime = false;
    while(!vTime){
        std::cout << "Time (HH:MM): ";
        std::getline(std::cin, time_str);
        vTime = validateTime(time_str);
        if (std::cin.eof()) {
            exitMenu();
        }
        else {
            std::cout << "Please enter a valid time: ";
        }

    }

    while(true){
        std::cout << "Number of carriages in transport car:";
        std::getline(std::cin, car_c);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(car_c)) {
            if (std::stoi(car_c) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }

    while(true){
        std::cout << "Number of carriages in transport car:";
        std::getline(std::cin, car_n);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(car_n)) {
            if (std::stoi(car_n) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
    while(true){
        std::cout << "Number of carriages in transport car:";
        std::getline(std::cin, car_m);
        if (std::cin.eof()) {
            exitMenu();
        }
        if (isAllDigits(car_m)) {
            if (std::stoi(car_m) > 0) {
                break;
            } else {
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        } else {
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
    auto origin_airport = airline.getAirport(departure);
    auto destination_airport = airline.getAirport(arrival);
    auto *flight = new Flight(origin_airport, destination_airport, plane2->getCapacity(), plane2->getCols(),
                              Date(stoi(year), stoi(month), stoi(day)), Time_m(time_str), stoi(duration), 0,
                              vector<Passenger>(), stoi(car_c), stoi(car_n), stoi(car_m));
    airline.addFlight(flight, plane2);
}

/**
 * Ask for an airport to aff
 * @param i
 */
void Menu::askForAirport(int i){
    string name, city, country;

    std::cout << "Airport " << i << std::endl;
    std::cout << "Specify the attributes of the airport you wish to add" << std::endl;
    while(true){

        std::cout << "Name (Type 0 to go back): ";
        std::getline(std::cin, name);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(name)){
            if (std::stoi(name) == 0) return;
        }
        if(!airline.airportExists(name)){
            break;
        }
        std::cout << "Airport already exists. Specify a new one or remove existing one!" << std::endl;
    }

    std::cout << "City: ";
    std::getline(std::cin, city);
    if (std::cin.eof()) {
        exitMenu();
    }

    std::cout << "Country: ";
    std::getline(std::cin, country);
    if (std::cin.eof()) {
        exitMenu();
    }
    airline.addAirport(new Airport(name, country, city));
}

void Menu::askForTransport(int i,Airport* airport) {
    std::string duration, initialTime, finalTime ,typeTransport, distance;
    vector<Time_m> horario;

    while(true){
        std::cout << "Type of Transport(bus, metro or train):";
        std::getline(std::cin, typeTransport);
        if (std::cin.eof()) {
            exitMenu();
        }
        while(typeTransport != "bus" && typeTransport != "metro" && typeTransport != "train"){
            std::cout << "Invalid Transport. Try Again!" << endl;
            std::cout << "Type of Transport(bus, metro or train):";
            std::getline(std::cin, typeTransport);
        }
        if((*airport).hasTransport(typeTransport)){
            cout << "Airport already has that type of transport"<< endl;
        }
        else break;
    }

    while(true){
        std::cout << "Distance from the airport:";
        std::getline(std::cin, distance);
        if (std::cin.eof()) {
            exitMenu();
        }
        if(isAllDigits(distance)){
            if (std::stoi(distance) > 0) break;
            else{
                cout << "Invalid distance!" << endl;
            }
        }
        else{
            cout << "Invalid distance!" << endl;
        }
    }
    //start time
    std::cout << "Initial Time (HH:MM): ";
    bool vTime_initial = false;
    std::getline(std::cin, initialTime);
    vTime_initial = validateTime(initialTime);
    while(!vTime_initial){
        std::cout << "Initial Time (HH:MM): ";
        std::getline(std::cin, initialTime);
        vTime_initial = validateTime(initialTime);
        if (std::cin.eof()) {
            exitMenu();
        }
        else {
            std::cout << "Please enter a valid time: ";
        }
    }
    //final time
    std::cout << "Final Time (HH:MM): ";
    bool vTime_final = false;
    std::getline(std::cin, finalTime);
    vTime_final = validateTime(finalTime);
    while(!vTime_final){
        std::cout << "Final Time (HH:MM): ";
        std::getline(std::cin, finalTime);
        vTime_final = validateTime(finalTime);
        if (std::cin.eof()) {
            exitMenu();
        }
        else {
            std::cout << "Please enter a valid time: ";
        }
    }
    //frequency
    std::cout << "Frequency (HH:MM): ";
    bool vTime_freq = false;
    std::getline(std::cin, duration);
    vTime_freq = validateTime(duration);
    while(!vTime_freq){
        std::cout << "Frequency (HH:MM): ";
        std::getline(std::cin, duration);
        vTime_freq = validateTime(duration);
        if (std::cin.eof()) {
            exitMenu();
        }
        else {
            std::cout << "Please enter a valid time: ";
        }
    }

    horario = createSchedule(initialTime,finalTime,duration);
    if(horario.empty()) {
        cout << "Invalid Schedule!"<< endl;
    }

    //TODO
    airport->addMeanOfTransport(MeanOfTransport(typeTransport,stoi(distance),horario,initialTime,finalTime,duration));
    airline.removeAllTransports();
    airline.storeAllTransports();
    airline.loadTransports();
    }

void Menu::askForWorker(int i) {
    string name;

    std::cout << "Worker " << i << std::endl;
    std::cout << "Specify the name of the worker you wish to add (Type 0 to go back):" << std::endl;
    std::getline(std::cin, name);
    if (std::cin.eof()) {
        exitMenu();
    }
    if(isAllDigits(name)){
        if (std::stoi(name) == 0) return;
    }
    airline.addWorker(name);
}

void Menu::exitMenu() {
    std::cout << "Come back any time soon!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Waits for 1 seconds before closing the window
    exit(EXIT_SUCCESS); // Closes the terminal window
}

void Menu::load() {
    airline.loadPlanes();
    airline.loadAirports();
    airline.loadFlights();
    airline.loadTransports();
    airline.loadWorkers();
    airline.loadServices();
    airline.loadTickets();
}