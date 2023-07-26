#include "Worker.h"
int Worker::current_id = 5000; //Worker ids start at 5000
Worker::Worker(const std::string& name) : Person(name) {
    this->name = name;
    this->worker_id = ++current_id;
}

int Worker::getId() const {
    return worker_id;
}

void Worker::resetId(){
    current_id = 5000;
}
