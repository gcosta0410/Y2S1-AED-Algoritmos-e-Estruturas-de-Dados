#ifndef AED2122_SERVICE_H
#define AED2122_SERVICE_H

#include "Date.h"
#include "Worker.h"

class Service {
    Date date;
    int worker_id; //Responsible worker for the service
    std::string type, plate; //type: whether "maintenance" or "cleaning"
    bool finished; //Whether the service has already occurred
public:
    Service(const string &plate, Date date, int worker_id, const string &type, bool finished): plate(plate), date(date), worker_id(worker_id), type(type), finished(finished){}
    Date getDate() const;
    int getWorkerId() const;
    std::string getType() const;
    std::string getPlanePlate() const;
    bool isFinished() const;
    bool operator== (const Service &service);
    void setFinished();
};


#endif //AED2122_SERVICE_H
