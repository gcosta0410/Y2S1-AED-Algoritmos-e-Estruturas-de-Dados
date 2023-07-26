#include "MeanOfTransport.h"
#include "AuxiliaryFunctions.h"
/**
 * Creates a transport with a type and schedule
 * @param type
 * @param distance
 * @param schedule
 * @param horaInicial
 * @param horaFinal
 * @param duration
 */
MeanOfTransport::MeanOfTransport(std::string type, unsigned int distance,std::vector<Time_m> &schedule,std::string horaInicial, std::string horaFinal, std::string duration) {
    this->type = type;
    this->distance = distance;
    sort(schedule.begin(), schedule.end(), compareTimes);
    this->schedule = schedule;
    this->initialTime = horaInicial;
    this->finalTime = horaFinal;
    this->duration = duration;
}
/**
 * A transport is lower than another if its distance to the airport is lower
 * @param mean2
 * @return
 */
bool MeanOfTransport::operator<(const MeanOfTransport &mean2) const {
    return this->distance < mean2.distance;
}
/**
 * Shows transport time and all of its schedules
 * @param out
 * @param tp
 * @return
 */
std::ostream &operator<<(std::ostream &out, const MeanOfTransport &tp) {
    out << tp.type << "\t" << tp.distance << "km away from the airport. " << std::endl;
    auto s = tp.schedule.size();
    for(unsigned long long i = 0; i < s; i++){
        out << "Departure: " << tp.schedule[i] << std::endl;
    }
    return out;

    //previously only printed the three schedules closest to the real time now;
//    Time_m now = getTimeNow();
//    if (s == 1) out << "Departure: " << tp.schedule[0]<< std::endl;
//    else if(s == 2) out << "Departure: " << tp.schedule[0] << std::endl << "Departure: " << tp.schedule[1] << std::endl;
//    else {
//        for (int i = 0; i < s; i++) {
//            if (timeIsBetween(now, tp.schedule[i], tp.schedule[(i+1)%s])) {
//                out << "Departure: " << tp.schedule[(i + 1) % s] << std::endl
//                          << "Departure: " << tp.schedule[(i + 2) % s] << std::endl
//                          << "Departure: " << tp.schedule[(i + 3) % s] << std::endl;
//                break;
//            }
//        }
//    }

}
/**
 * Prints at most the 3 schedules closer to the real time now
 */
void MeanOfTransport::showNearestSchedules() const{
    Time_m now = getTimeNow();
    auto s = schedule.size();
    if (s == 0) std::cout << "Sorry, we could not find any schedule for that transport." << std::endl;
    if (s == 1) std::cout << "Departure: " << schedule[0] << std::endl;
    else if(s == 2) std::cout << "Departure: " << schedule[0] << std::endl << "Departure: " << schedule[1] << std::endl;
    else {
        for (unsigned long long i = 0; i < s; i++) {
            if (timeIsBetween(now, schedule[i], schedule[(i+1)%s])) {
                std::cout << "Departure: " << schedule[(i + 1) % s] << std::endl
                          << "Departure: " << schedule[(i + 2) % s] << std::endl
                          << "Departure: " << schedule[(i + 3) % s] << std::endl;
                break;
            }
        }
    }
}

std::string MeanOfTransport::getType() const {
    return type;
}
/**
 * Gets the schedule closest to the real time now
 * @return
 */
Time_m MeanOfTransport::getNearestSchedule() const {
    Time_m now = getTimeNow();
    auto s = schedule.size();
    for (unsigned long long i = 0; i < s; i++) {
        if (timeIsBetween(now, schedule[i], schedule[(i+1)%s])) {
            return schedule[(i+1)%s];
        }
    }
    std::cerr << "Could not find a schedule!" << std::endl;
    return {23, 59};
}

const string &MeanOfTransport::getInitialHour() const {
    return initialTime;
}

const string &MeanOfTransport::getFinalHour() const {
    return finalTime;
}

const string &MeanOfTransport::getDuration() const {
    return duration;
}

unsigned int MeanOfTransport::getDistance() const {
    return distance;
}
