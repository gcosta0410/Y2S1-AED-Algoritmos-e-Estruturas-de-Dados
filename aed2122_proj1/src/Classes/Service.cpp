#include "Service.h"

Date Service::getDate() const {
    return this->date;
}

int Service::getWorkerId() const {
    return this->worker_id;
}

string Service::getType() const{
    return this->type;
}

string Service::getPlanePlate() const{
    return this->plate;
}

bool Service::isFinished() const{
    return this->finished;
}
/**
 * Two services are equal if they share exactly the same attributes
 * @param service1
 * @return
 */
bool Service::operator==(const Service &service1){
    return (this->date == service1.getDate() && this->worker_id == service1.getWorkerId() && this->type == service1.getType() && this->plate == service1.getPlanePlate() && this->finished == service1.isFinished());
}
/**
 * Mark the service as finished
 */
void Service::setFinished() {
    this->finished = 1;
}