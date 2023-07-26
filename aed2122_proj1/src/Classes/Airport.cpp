//
// Created by jcarv on 04/12/2021.
//

#include <algorithm>
#include "Airport.h"
#include "AuxiliaryFunctions.h"


std::string Airport::getName() const {
    return name;
}
std::string Airport::getCountry() const{
    return country;
}
std::string Airport::getCity() const{
    return city;
}
/**
 * To airports are equal if they have the same name. Unique names are assumed. Used for search purposes
 * @param apt
 * @return
 */
bool Airport::operator==(const Airport &apt) const {
    return toLowerStr(apt.name) == toLowerStr(name);
}
/**
 *
 * @param num defines how many transports to show at most
 */
void Airport::showTransports(unsigned int num) {
    if (num == -1) num = DEFAULT_NUMBER_OF_TRANSPORTS;
    else if (num == 0) {
        showAllTransports();
        return;
    }
    std::cout << "Here are the means of transport closest to the airport:" << std::string(2, '\n');
    unsigned count = 0;
    for(auto it = transports.begin(); it != transports.end() && count < num ; it++){
        std::cout << (*it) << std::endl;
        count++;
    }
}

void Airport::showAllTransports() {
    std::cout << "Here are all the means of transport close to the airport:" << std::string(2, '\n');
    for(auto it = transports.begin(); it != transports.end(); it++){
        std::cout << (*it) << std::endl;
    }
}
/**
 * Show at most num transports from type (bus, metro or train)
 * @param type
 * @param num
 */
void Airport::showTransports(const std::string& type, unsigned int num) {
    if (num == -1) num = DEFAULT_NUMBER_OF_TRANSPORTS;
    else if (num == 0) num = INT32_MAX; //Ensures all transports are shown
    bool found = false;
    for(auto it = transports.begin(); it != transports.end() && num > 0; it++){
        if ((*it).getType() == type) {
            found = true;
            std::cout << (*it) << std::endl;
            num--;
        }
    }
    if (!found) std::cout << "Sorry, could not find matching transports." << std::endl;
}
/**
 * Shows transports sorted by the temporal proximity to the real time now
 * @param num
 */
void Airport::showTransportsByTime(unsigned int num) {
    std::vector<MeanOfTransport> tps;
    for(auto it = transports.begin(); it != transports.end(); it++){
        tps.push_back((*it));
    }
    sort(tps.begin(), tps.end(), [](const MeanOfTransport& t1, const MeanOfTransport& t2){
        return t1.getNearestSchedule() < t2.getNearestSchedule();
         }
    );
    if (num == -1) num = DEFAULT_NUMBER_OF_TRANSPORTS;
    else if (num == 0) {
        num = INT32_MAX;
        return;
    }
    for(int i = 0; i < tps.size() && num > 0 ;i++, num--){
        std::cout << tps[i] << std::endl;
    }
}

void Airport::addMeanOfTransport(const MeanOfTransport& mean) {
    transports.insert(mean);
}
/**
 * Checks if there are no transports in the airport
 * @return
 */
bool Airport::noTransports() {
    return transports.isEmpty();
}

/**
 * Check is the airport has any transport of the requested type
 * @param typeTransport
 * @return
 */
bool Airport::hasTransport(const std::string& typeTransport) {
    BSTItrIn<MeanOfTransport> itr(transports);
    while(!itr.isAtEnd()){
        if(itr.retrieve().getType() == typeTransport) return true;
        itr.advance();
    }
    return false;
}

const BST<MeanOfTransport> &Airport::getTransports() const {
    return transports;
}

/**
 * Erase all transports
 */
void Airport::emptyTransports() {
    transports.makeEmpty();
}
/**
 * Erase all trasnports from a certain type
 * @param type
 */
void Airport::removeTransport(const std::string& type) {
    BSTItrIn<MeanOfTransport> itr(transports);
    while(!itr.isAtEnd()){
        if(itr.retrieve().getType()==type) transports.remove(itr.retrieve());
        itr.advance();
    }
}

