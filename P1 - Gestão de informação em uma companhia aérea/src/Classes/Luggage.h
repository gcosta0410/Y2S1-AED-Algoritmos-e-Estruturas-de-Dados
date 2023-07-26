#ifndef AED2122_LUGGAGE_H
#define AED2122_LUGGAGE_H


#include <ostream>

class Luggage {
private:
    unsigned int owner_id;
    unsigned int weight;
    bool in_car; //If the owner chose to automatically hceck-in the baggage
public:
    Luggage(unsigned int id, unsigned int weight, bool in_car = false);
    Luggage();
    void setId(int owner_id);
    bool notEmpty() const;
    unsigned int getWeight() const;
    bool getIsInCar() const;
};


#endif //AED2122_LUGGAGE_H
