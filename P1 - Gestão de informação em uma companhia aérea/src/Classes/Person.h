#ifndef AED2122_PERSON_H
#define AED2122_PERSON_H

#include <string>

class Person {
public:
    explicit Person(const std::string &name);
    std::string getName() const;
    void setName(std::string &name);
protected:
    std::string name;
};

#endif //AED2122_PERSON_H
