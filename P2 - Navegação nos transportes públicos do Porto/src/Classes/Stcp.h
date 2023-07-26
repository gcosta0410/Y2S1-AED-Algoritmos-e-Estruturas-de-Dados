#ifndef AED2122_TRABALHO2_STCP_H
#define AED2122_TRABALHO2_STCP_H

#include <unordered_map>
#include "graph.h"
#include "LineGraph.h"

struct Stop{
    string name;
    double lat, lon;
    string code;
};

class Stcp {

private:
    bool walk = false;
    double dist = -1;
    bool diurno;
    bool global;

    int numberOfStops;
    struct Stop startStop;
    struct Stop endStop;
    Graph graph; //nós = paragens, arestas = distâncias
    LineGraph lineGraph; //nós = <paragem, linha>, arestas = <mudança de linha, mudança de nó>
    std::unordered_map<std::string,int> index; // código-índice
    std::unordered_multimap<std::string,int> multiIndex; // código-índices
    std::unordered_map<std::string,int> specificIndex; //código + linha - índice
    std::unordered_map<int,std::string> indexReverse;
    std::unordered_map<std::string,std::string> codeToName;
    void loadStops();
    void loadLineInfo(const std::string& code);
    void loadLines();


public:
    Stcp();
    void load();
    double bestDistance(const string& code1,const string& code2);
    const unordered_map<std::string, int> &getIndex() const;
    const unordered_map<std::string, std::string> &getCodeToName() const;
    void setStartName(const string& name); //startStop.name = name;
    void setStartCoords(double lat, double lon);
    void setStartCode(const string& code);
    void setEndName(const string& name);
    void setEndCoords(double lat, double lon);
    void setEndCode(const string& code);
    const Stop &getStartStop() const;
    const Stop &getEndStop() const;
    void setDiurno();
    void setNoturno();
    bool isDiurno();
    void setGlobal(bool flag);
    bool isGlobal();

    void loadLineGraph();

    void loadWalks();

    bool hasRoute(int i, int j);
    void leastLineChanges(const string& code1, const string& code2);
    void leastStopsWithLeastLines(const string& code1, const string& code2);
    void leastZoneChanges(const string& code1, const string& code2);
    void leastStops(const string& code1, const string& code2);
    std::vector<std::string> nearestStop(const double& latitude, const double& longitude, const double& radius);
    double globalMST();

    bool walkValid() const;
    void setWalkValid();
    void setWalkInvalid();
    double getDistofWalk() const;

    void setDist(double dist);

    std::string getStartCode();

    std::string getEndCode();

    void clear();

    vector<string> getCodes(std::string name);
};


#endif //AED2122_TRABALHO2_STCP_H
