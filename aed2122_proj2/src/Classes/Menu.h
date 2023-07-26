#ifndef AED2122_TRABALHO2_MENU_H
#define AED2122_TRABALHO2_MENU_H

#include "Stcp.h"

class Menu {
private:
    Stcp stcp;
    void load();
public:
    void mainMenu();
        void stcpMenu();
            bool chooseMethodMenu(bool start);
                void defineStopMenu(int opt, bool start);
        bool chooseStopMenu(int i, bool start);
            void chooseRouteMenu();
                void walkMenu();
                void distanceMenu();
                void showBestDistanceRoute();
                void showLeastStopsRoute();
                void showLeastLinesRoute();
                void showLeastZoneChangesRoute();
                void diurnoNoturnoMenu();
                void MSTMenu();
                void showLeastLinesWithLeastStopsRoute();

    static void exitMenu();
};

#endif //AED2122_TRABALHO2_MENU_H
