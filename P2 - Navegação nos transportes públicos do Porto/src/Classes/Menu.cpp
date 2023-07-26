#include <iostream>
#include <thread>
#include "Menu.h"
#include "AuxiliaryFunctions.h"


/**
 * Main menu
 */
void Menu::mainMenu() {

    string option;

    // Ask for a valid input
    cout << "-----------------------------------\n"
            "|  Transportes publicos do Porto  |\n"
            "-----------------------------------" << endl;

    while (true) {

        cout << "1.Planear Viagem" << endl;
        cout << "2.MST da Rede STCP" << endl;
        cout << "0.Sair" << endl;
        cout << "Selecione o pretendido:";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(2,option);
        if(correct){
            switch (std::stoi(option)) {

                case 1:
                    stcpMenu();
                    break;
                case 2:
                    MSTMenu();
                    break;
                case 0:
                    exitMenu();
                    return;
            }
        }
    }
}

/**
 * First sub-menu, to plan a bus trip
 */
void Menu::stcpMenu() {
    cout << endl;
    diurnoNoturnoMenu();
    load();
    bool back = chooseMethodMenu(true);
    if(back){
        return;
    }
    back = chooseMethodMenu(false);
    if(back){
        return;
    }
    chooseRouteMenu();
}

/**
 * Second sub-menu, to check the MST of the entire STCP network
 */
void Menu::MSTMenu(){
    string option;
    while(true){
        cout << endl;
        cout << "Deseja ver a Minimum spanning tree da rede STCP... "<< endl;
        cout << "1.Global" << endl;
        cout << "2.Diurna" << endl;
        cout << "3.Noturna" << endl;
        cout << "4.Back" << endl;
        cout << "0.Sair" << endl;
        cout << "Selecione uma opcao das anteriores:";
        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if(correct){
            switch (std::stoi(option)) {
                case 1: {
                    stcp.setGlobal(true);
                    break;
                }
                case 2:
                    stcp.setGlobal(false);
                    stcp.setDiurno();
                    break;
                case 3:
                    stcp.setGlobal(false);
                    stcp.setNoturno();
                    break;
                case 4:
                    cout << endl;
                    cout << "-----------------------------------\n"
                            "|  Transportes publicos do Porto  |\n"
                            "-----------------------------------" << endl;
                    return;
                case 0:
                    exitMenu();
                    return;
            }
            load();
            cout<< endl;
            stcp.globalMST();
        }
    }
}

/**
 * Menu to choose between day and night trip
 */
void Menu::diurnoNoturnoMenu(){
    string option;
    stcp.setGlobal(false);

    // Ask for a valid input
    while (true) {

        cout << "1.Diurno" << endl;
        cout << "2.Noturno" << endl;
        cout << "0.Sair" << endl;
        cout << "Selecione o tipo de horario no qual pretende viajar:";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(2, option);
        if (correct) {
            switch (std::stoi(option)) {

                case 1:
                    stcp.setDiurno();
                    return;

                case 2:
                    stcp.setNoturno();
                   return;

                case 0:
                    exitMenu();
                    return;
            }
        }
    }
}

/**
 * Menu to choose the input method for the start and end stops
 * @param start
 * @return
 */
bool Menu::chooseMethodMenu(bool start){
    string option;
    bool found;

    // Ask for a valid input
    while (true) {
        cout << endl;

        cout << "1.Introduzir coordenadas" << endl;
        cout << "2.Introduzir nome" << endl;
        cout << "3.Introduzir codigo" << endl;
        cout << "4.Voltar" << endl;
        cout << "0.Sair" << endl;
        cout << "Escolha a maneira que pretende definir a paragem de " << ((start) ?  "partida:" : "chegada:");

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(4,option);
        if(correct){
            switch (std::stoi(option)) {

                case 1:
                case 2:
                case 3:
                    defineStopMenu(std::stoi(option), start);
                    found = chooseStopMenu(std::stoi(option), start);
                    return !found;
                case 4:
                    return true;
                case 0:
                    exitMenu();
            }
        }
    }
}

/**
 * Menu to actually input stop info
 * @param i
 * @param start
 */
void Menu::defineStopMenu(int i, bool start){
    string optionaux;
    switch (i) {
        case 1: {
            string coords;
            double lat, lon;
            while (true) {
                cout << R"(Introduza as coordendas no formato "41.18332779 -8.600504312": )";
                std::getline(std::cin, coords);
                // Check for CTRL + Z or CTRL + D input to close the program
                if (std::cin.eof()) {
                    exitMenu();
                }
                if (validCoords(coords, lat, lon)) {
                    if (start) stcp.setStartCoords(lat, lon);
                    else stcp.setEndCoords(lat, lon);
                    break;
                }
            }
            break;
        }

        //nome
        case 2:
            while (true) {
                cout << "Introduza o nome da Paragem:";
                std::getline(std::cin, optionaux);
                // Check for CTRL + Z or CTRL + D input to close the program
                if (std::cin.eof()) {
                    exitMenu();
                }
                if(!validName(optionaux,stcp.getCodeToName())){
                    std::cerr << std::endl << "A paragem nao é valida!" << std::endl << std::endl;
                }
                else {
                    if(start) stcp.setStartName(optionaux);
                    else stcp.setEndName(optionaux);
                    break;
                }
            }
            break;
        //codigo
        case 3:
            while (true) {
                cout << "Introduza o codigo da Paragem:";
                std::getline(std::cin, optionaux);
                // Check for CTRL + Z or CTRL + D input to close the program
                if (std::cin.eof()) {
                    exitMenu();
                }
                if(!validCode(optionaux,stcp.getIndex())){
                    std::cerr << std::endl << "A paragem nao é valida!!" << std::endl << std::endl;
                }
                else {
                    if(start) stcp.setStartCode(optionaux);
                    else stcp.setEndCode(optionaux);
                    cout << "A paragem foi encontrada" << endl;
                    break;
                }
            }

            break;
    }
}

/**
 * Menu to choose between different stops with similar/same info
 * @param i
 * @param start
 * @return
 */
bool Menu::chooseStopMenu(int i, bool start){

    std::vector<string> stops;
    switch (i) {
        case 1: {
            string option;
            // Ask for a valid input
            while (true) {
                if (start) {
                    stops = stcp.nearestStop(stcp.getStartStop().lat, stcp.getStartStop().lon, 0.100);
                } else {
                    stops = stcp.nearestStop(stcp.getEndStop().lat, stcp.getEndStop().lon, 0.100);
                }
                if(stops.empty()) { cout << "Nao ha paragens perto dessa localizacao. Redifina as coordenadas" << std::endl << std::endl; return false;}
                std::cout << "As paragens perto da sua localizacao sao: " << std::endl;
                int j = 1;
                for (const auto &code: stops) {
                    std::cout << j << ")" << code << ": " << stcp.getCodeToName().at(code)
                              << std::endl; //adicionar linha à paragem e mostar aqui??
                    j++;
                }
                cout << "Escolha a paragem que pretende: ";

                std::getline(std::cin, option);
                // Check for CTRL + Z or CTRL + D input to close the program
                if (std::cin.eof()) {
                    exitMenu();
                }
                bool correct = parseInput(stops.size(), option);
                if (correct) {
                    if (start) {
                        stcp.setStartCode(stops.at(stoi(option)-1));
                    } else {
                        stcp.setEndCode(stops.at(stoi(option)-1));
                    }
                    break;
                }
            }
            break;
        }
        case 2:{
            string option;
            // Ask for a valid input
            while (true) {
                if (start) {
                    stops = stcp.getCodes(stcp.getStartStop().name);
                } else {
                    stops = stcp.getCodes(stcp.getEndStop().name);
                }
                std::cout << "As paragens com o seguinte nome sao: " << std::endl;
                int j = 1;
                for (const auto &code: stops) {
                    std::cout << j << ")" << code << ": " << stcp.getCodeToName().at(code)
                              << std::endl; //adicionar linha à paragem e mostar aqui??
                    j++;
                }
                cout << "Escolha a paragem que pretende: ";

                std::getline(std::cin, option);
                // Check for CTRL + Z or CTRL + D input to close the program
                if (std::cin.eof()) {
                    exitMenu();
                }
                bool correct = parseInput(stops.size(), option);
                if (correct) {
                    if (start) {
                        stcp.setStartCode(stops.at(stoi(option)-1));
                    } else {
                        stcp.setEndCode(stops.at(stoi(option)-1));
                    }
                    break;
                }
            break;
            }
        }

        case 3:
            break;
    }
    return true;
}

/**
 * Menu to choose route wanted to be calculated
 */
void Menu::chooseRouteMenu() {
    string option;
    while (true) {
        cout << endl;

        cout << "Existem varias opcoes de calculo de percurso:" << endl;
        cout << "1.Menor numero de paragens durante a viagem" << endl;
        cout << "2.Menor distancia percorrida" << endl;
        cout << "3.Menor mudanca de autocarros" << endl;
        cout << "4.Menor preco" << endl;
        cout << "5.Menor numero de paragens e menor numero de troca de autocarros" << endl;
        cout << "6.Voltar" << endl;
        cout << "0.Sair" << endl;
        cout << "Selecione a que melhor se adequa a si:";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(7,option);
        if(stoi(option) == 6){cout << endl; return;}
        if(stoi(option) == 0){exitMenu();}
        walkMenu();
        if(stcp.walkValid()){
            distanceMenu();
        }
        load();
        if(correct){
            switch (std::stoi(option)) {

                case 1:
                    showLeastStopsRoute();
                    break;
                case 2:
                    showBestDistanceRoute();
                    break;
                case 3:
                    showLeastLinesRoute();
                    break;
                case 4:
                    showLeastZoneChangesRoute();
                    break;
                case 5:
                    showLeastLinesWithLeastStopsRoute();
                    break;
            }
        }
    }
}

/**
 * Menu to choose if the user wants to walk or not
 */
void Menu::walkMenu() {
    string option;
    while (true) {
        cout << endl;
        cout << "Pretende que um percurso a pe seja tido em consideracao no calculo do percurso?" << endl;
        cout << "1.Sim" << endl;
        cout << "2.Nao" << endl;
        cout << "0.Sair" << endl;
        cout << "ATENCAO - E possivel que caminhar um pouco ate uma dada paragem seja benefico" << endl;
        cout << "Indique uma das opcoes:";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool correct = parseInput(2,option);
        if(correct){
            switch (std::stoi(option)) {
                case 1:
                    stcp.setWalkValid();
                    return;
                case 2:
                    stcp.setWalkInvalid();
                    return;
                case 0:
                    exitMenu();
                    break;
            }
        }
    }

}

/**
 * Menu to set maximum walking distance
 */
void Menu::distanceMenu() {
    string option;
    while (true) {
        cout << endl;
        cout << "A distancia deve ser inferior a 0.400 Km por motivos de complexidade temporal" << endl;
        cout << "0.Exit"<< endl;
        cout << "Introduza a distancia maxima que tolera ser percorrida a pe (recomendado:0.150 km):";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        if(!isDouble(option)){
            std::cerr<<std::endl<< "Input invalido!" << std::endl;
        }
        else if(stod(option)<=0){
            std::cerr<< std::endl << "Numero invalido!" << std::endl;
        }
        else if(stod(option)>=0.4){
            std::cerr<< std::endl << "Numero demasiado alto! (Distancia deve ser entre 0 e 0.400 Km)" << std::endl;
        }
        else{
            stcp.setDist(stod(option));
            std::cout << endl;
            break;
        }

    }
}

/**
 * Calculates best distance route
 */
void Menu::showBestDistanceRoute() {
    stcp.bestDistance(stcp.getStartCode(),stcp.getEndCode());
}

/**
 * Calculates least stops route
 */
void Menu::showLeastStopsRoute() {
    stcp.leastStops(stcp.getStartCode(),stcp.getEndCode());
}

/**
 * Calculates least lines route
 */
void Menu::showLeastLinesRoute() {
    stcp.leastLineChanges(stcp.getStartCode(),stcp.getEndCode());
}
/**
 * Calculates least zone changes route
 */
void Menu::showLeastZoneChangesRoute() {
    stcp.leastZoneChanges(stcp.getStartCode(),stcp.getEndCode());
}
/**
 * Calculetes least lines and least stops rout
 */
void Menu::showLeastLinesWithLeastStopsRoute() {
    stcp.leastStopsWithLeastLines(stcp.getStartCode(), stcp.getEndCode());
}
/**
 * Exits the program
 */
void Menu::exitMenu() {
    std::cout << "Come back any time soon!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Waits for 1 seconds before closing the window
    exit(EXIT_SUCCESS); // Closes the terminal window
}
/**
 * Loads all the needed info
 */
void Menu::load() {
    stcp.load();
}

