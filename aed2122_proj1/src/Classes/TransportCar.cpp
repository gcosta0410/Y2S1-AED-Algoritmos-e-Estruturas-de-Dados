#include <queue>
#include <iostream>
#include "TransportCar.h"

TransportCar::TransportCar(unsigned int c, unsigned int n, unsigned int m) {
    this->c = c;
    this->n = n;
    this->m = m;
    car.resize(c);
    for(auto &carriage :car){
        carriage.resize(n);
        }
}

bool TransportCar::addToConveyor(const Luggage& lug) {
    if(conveyor.size() + 1 <= n * c * m){
        conveyor.push(lug);
        return true;
    }
    return false;
}

TransportCar::TransportCar() {
    conveyor = std::queue<Luggage>();
    car = std::list<std::list<std::stack<Luggage>>>();
}


void TransportCar::loadToCar() {
    bool flag = false;
    while(!conveyor.empty()){
        Luggage lug = conveyor.front();
        conveyor.pop();
        for(auto it =  car.rbegin(); it != car.rend();it++){
            flag = false;
            for(auto jt = (*it).rbegin();jt != (*it).rend(); jt++){
                if ((*jt).size() == m){
                    continue;
                }
                else{
                    (*jt).push(lug);
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
    }
}

void TransportCar::showCar() const{
    std::cout << "Carriages: " << c << "\t" << "Stacks per carriage: " << n <<"\t" << "Maximum items per stack: " << m <<std::endl;
    for(auto it =  car.begin(); it != car.end();it++){
        std::cout<<"|";
        for(auto jt = (*it).begin();jt != (*it).end(); jt++){
            std::cout << (*jt).size() << "|";
            }
        std::cout <<"\t";
        }
    std::cout<<std::endl;
}

unsigned int TransportCar::getC() const {
    return c;
}
unsigned int TransportCar::getM() const {
    return m;
}
unsigned int TransportCar::getN() const {
    return n;
}
