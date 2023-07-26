#include <iostream>
#include "AuxiliaryFunctions.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cmath>
#include <sstream>


/**
 * Get a yes ('Y') or no ('N') answer
 * @return true if Yes, false if No
 */
bool getAnswer() {
    char answer;
    answer = toupper(getChar());
    while (!(('Y' == answer) || ('N' == answer))) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid answer! Enter again: ";
        answer = toupper(getChar());
    }
    return (answer == 'Y');
}


/**
 * Checks if a string represents a number
 * @param str
 * @return
 */
bool isAllDigits(const std::string &str){

    // Iterates each character in a std::string and checks if it's an integer or not
    if(str.empty()) return false;
    for(char c: str){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

/**
 * Checks if a string represents a number in more compact way
 * @param s
 * @return
 */
bool isNumber(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

/**
 * Check if a number in the correct interval (0 to a) is inputted
 * @param a
 * @param text
 * @return
 */
bool parseInput(int a, const std::string& text){
    std::vector<int> values;
    for(int i = 0; i <= a; i++){
        values.push_back(i);
    }
    auto it = values.begin();
    if (isAllDigits(text)) {
        it = std::find(values.begin(), values.end(), stoi(text));
        if (it != values.end()) {
            return true;
        } else {
            std::cerr << std::endl << "Input inválido!" << std::endl << std::endl;
        }
    } else {
        std::cerr << std::endl << "Input inválido!" << std::endl << std::endl;
    }
    return false;
}

char getChar() {
    char letter;
    std::cin >> letter;
    while (std::cin.peek() != '\n' || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input! Enter again: ";
        std::cin >> letter;
    }
    return letter;
}


/**
 * Calculates distance between 2 coordinate pairs
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return
 */
double haversine(double lat1, double lon1,
                        double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/**
 * Checks if an input string represents a valid coordinate pair
 * @param coords
 * @param lat
 * @param lon
 * @return
 */
bool validCoords(const std::string& coords, double &lat, double &lon){

    std::istringstream ss(coords);
    std::string del;
    std::vector<std::string> aux;
    while(getline(ss, del, ' ')) {
        aux.push_back(del);
    }

    if(aux.size()!= 2){
        std::cerr << "Input invalido, por favor especifique as coordenadas de forma correta i.e. ""41.18332779 -8.600504312""" << std::endl;
        return false;
    }

    size_t found;
    std::string aux1;
    for(auto &coord : aux){
        found = coord.find('.');
        if(found == std::string::npos){
            std::cerr << "Input invalido, por favor especifique as coordenadas de forma correta i.e. ""41.18332779 -8.600504312""" << std::endl;
            return false;
        }
        aux1 = coord;
        aux1.erase(found, 1);
        if(aux1.at(0) == '-') {
            aux1.erase(0,1);
            if (!isAllDigits(aux1)) {
                std::cerr
                        << "Input invalido, por favor especifique as coordenadas de forma correta i.e. ""41.18332779 -8.600504312"""
                        << std::endl;
                return false;
            }
        }
    }

    double temp_lat = std::stod(aux.at(0));
    double temp_lon = std::stod(aux.at(1));

    if((temp_lat < 41 || temp_lat > 43) || (temp_lon < -9 || temp_lon > -7)){
        std::cerr << "Nao ha paragens perto da localizacao selecionada. Tem a certeza que esta no Porto?" << std::endl;
        return false;
    }

    lat = std::stod(aux.at(0));
    lon = std::stod(aux.at(1));

    return true;

}

/**
 * Checks if an input string represents a valid stop code
 * @param name
 * @param paragens
 * @return
 */
bool validCode(const std::string& name, const std::unordered_map<std::string,int>& paragens) {
    for (const auto &paragem: paragens) {
        if (paragem.first == name) return true;
    }
    return false;
}

/**
 * Checks if a string represents a valid stop name
 * @param name
 * @param paragens
 * @return
 */
bool validName(const std::string& name, const std::unordered_map<std::string,std::string>& paragens){
    for(const auto& paragem : paragens){
        if(paragem.second == name) return true;
    }
    return false;
}

/**
 * Checks if a string represents a double value
 * @param s
 * @return
 */
bool isDouble(const std::string& s)
{
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}