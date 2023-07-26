#include "Person.h"


Person::Person(const std::string &name) {
    this->name = name;
}

std::string Person::getName() const{
    return name;
}

void Person::setName(std::string &new_name){
    this->name = new_name;
}