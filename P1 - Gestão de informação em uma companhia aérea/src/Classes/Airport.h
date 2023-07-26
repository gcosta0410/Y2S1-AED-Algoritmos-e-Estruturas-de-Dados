#ifndef AED2122_AIRPORT_H
#define AED2122_AIRPORT_H

#include <string>
#include "MeanOfTransport.h"
#include "bst.h"
#define DEFAULT_NUMBER_OF_TRANSPORTS 3

class Airport {
private:
    std::string name;
    std::string country;
    std::string city;
    BST<MeanOfTransport> transports = BST<MeanOfTransport>(MeanOfTransport());
public:
    Airport(std::string name, std::string country = "", std::string city = ""): name(name), country(country), city(city){};
    Airport(){name = ""; country = ""; city = "";};
//    Airport(){Airport(""); transports = BST<MeanOfTransport>(MeanOfTransport());}
    std::string getName() const;
    std::string getCountry() const;
    std::string getCity() const;
    bool operator==(const Airport& apt) const;
    void showTransports(unsigned int num = DEFAULT_NUMBER_OF_TRANSPORTS); //por default ordenados por distancia e só mostra xx
    void showTransports(const std::string& type, unsigned int num = DEFAULT_NUMBER_OF_TRANSPORTS); //bus, metro, train
    void showTransportsByTime(unsigned int num = DEFAULT_NUMBER_OF_TRANSPORTS); //mostra primeiro o próximo a partir
    void showAllTransports(); // lista todos os transportes por distância
    bool hasTransport(const std::string& typeTransport);
    void addMeanOfTransport(const MeanOfTransport& mean);
    void removeTransport(const std::string& type);
    void emptyTransports();
    bool noTransports();
    const BST<MeanOfTransport> &getTransports() const;
};


#endif //AED2122_AIRPORT_H
