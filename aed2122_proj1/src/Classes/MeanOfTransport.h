#ifndef AED2122_MEANOFTRANSPORT_H
#define AED2122_MEANOFTRANSPORT_H


#include <string>
#include <vector>
#include "Time_m.h"

class MeanOfTransport {
private:
    std::string type;
    unsigned int distance;
    std::vector<Time_m> schedule;
    std::string initialTime, finalTime, duration; //Needed to store in the file new schedules
public:
    MeanOfTransport(std::string type, unsigned int distance, std::vector<Time_m> &schedule,std::string initial_hour, std::string final_hour, std::string duration);
    MeanOfTransport():type(""),distance(0), schedule(std::vector<Time_m>()){}
    Time_m getNearestSchedule() const;
    void showNearestSchedules() const;
    const std::string &getDuration() const;
    const std::string &getInitialHour() const;
    const std::string &getFinalHour() const;
    std::string getType() const;
    unsigned int getDistance() const;
    bool operator<(const MeanOfTransport& mean2) const;
    friend std::ostream& operator<<(std::ostream& out, const MeanOfTransport& tp);
};

#endif //AED2122_MEANOFTRANSPORT_H
