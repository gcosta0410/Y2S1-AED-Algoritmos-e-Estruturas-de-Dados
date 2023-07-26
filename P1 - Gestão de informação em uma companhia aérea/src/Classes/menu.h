#ifndef AED2122_MENU_H
#define AED2122_MENU_H

#include <ctime>
#include "Airline.h"

class Menu {
private:
    Airline airline;
    void load();
public:
    void mainMenu();
    void clientMenu();
        void buyTicketsMenu();
        void clientTransportsMenu();
    void adminMenu();
        void planesMenu();
            void planesManagementMenu();
                void addPlanesMenu();
                void removePlanesMenu();
                void showPlanesMenu();
            void servicesManagementMenu();
                void addServicesMenu();
                void removeServicesMenu();
                void updateServicesMenu();
                void showServicesMenu();//TODO * and show filters (all, by type, finished or unfinished)
            void flightsManagementMenu();
                void addFlightsMenu();
                void removeFlightsMenu();
                void updateFlightsMenu();
                void showFlightsMenu();
        void airportsMenu();
            void addAirportsMenu();
            void removeAirportsMenu();
            void showAirportsMenu();
        void transportsMenu();
            void addTransportsMenu();
            void removeTransportsMenu();
            void showTransportsMenu();
        void workersMenu();
            void addWorkersMenu();
            void removeWorkersMenu();
            void showWorkersMenu();
        void passengersMenu();
            void showPassengersMenu();
    static void exitMenu();

    void askForPlane(int i);
    Service* askForService(const string& plate);
    void askForFlight(int i);
    void askForAirport(int i);
    void askForWorker(int i);
    void askForTransport(int i, Airport* airport);
};


#endif //AED2122_MENU_H