#ifndef AED2122_WORKER_H
#define AED2122_WORKER_H


#include "Person.h"

class Worker: public Person {
private:
    int worker_id;
public:
    static int current_id;
    explicit Worker(const std::string& name);
    int getId() const;
    static void resetId();
};


#endif //AED2122_WORKER_H
