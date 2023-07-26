#ifndef MAIN_CPP_TRANSPORTCAR_H
#define MAIN_CPP_TRANSPORTCAR_H

#include "Luggage.h"
#include <stack>
#include <list>
#include <string>


class TransportCar {
private:
    std::list<std::list<std::stack<Luggage>>> car;
    std::queue<Luggage> conveyor;
    unsigned int n, c, m;
public:
    TransportCar(unsigned int c, unsigned int n, unsigned int m);
    TransportCar();
    bool addToConveyor(const Luggage& lug);
    void loadToCar();
    void showCar() const;
    unsigned int getC() const;
    unsigned int getN() const;
    unsigned int getM() const;



};


#endif //MAIN_CPP_TRANSPORTCAR_H
