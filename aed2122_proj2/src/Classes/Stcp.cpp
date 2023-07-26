#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Stcp.h"
#include "AuxiliaryFunctions.h"

Stcp::Stcp() {
    string line;
    int count = 0;
    ifstream file("dataset/stops.csv");
    if(file.is_open())
    {
        while(!file.eof())
        {
            getline(file,line);
//            cout<< line << endl;
            count++;
        }
        file.close();
    }
    count--;
    numberOfStops = count;
    graph = Graph(numberOfStops,true);
}

/**
 * Clears the current graphs and loads them again
 */
void Stcp::load() {
    clear();
    loadStops();
    loadLines();
    loadLineGraph();
}

/**
 * Reads a specific line and adds the respective edges
 * @param code
 */
void Stcp::loadLineInfo(const std::string& code) {
    std::string line, word;
    std::vector<std::string> row;
    std::vector<std::string> dirs({"_0","_1"});
    std::vector<std::string> paragens;
    for(const auto& dir:dirs){
        std::fstream file ("dataset/line_" + code + dir + ".csv", std::ios::in);
        int count = -1;
        if(file.is_open()){
            while(getline(file, line)) {
                count++;
                if (count == 0) continue;
                row.clear();
                std::stringstream str(line);
                while (getline(str, word, ',')) {
                    row.push_back(word);
                }
                paragens.push_back(row.at(0));
            }
            for (int stop = 1;  stop< paragens.size(); stop++){
                string stopInicial = paragens.at(stop-1);
                string stopFinal = paragens.at(stop);
                double weight = haversine(graph.nodes[index[stopInicial]].latitude,graph.nodes[index[stopInicial]].longitude,graph.nodes[index[stopFinal]].latitude,graph.nodes[index[stopFinal]].longitude);
                graph.addEdge(index[stopInicial],index[stopFinal],weight, code + dir);
            }
            paragens.clear();
            file.close();
        }
        else
            std::cerr<<"Could not open the file\n";
    }
}

/**
 * Reads all Lines or the daytime or nighttime lines
 */
void Stcp::loadLines() {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file ("dataset/lines.csv", std::ios::in);
    int count = -1;
    if(file.is_open()){
        while(getline(file, line)) {
            count++;
            if (count == 0) continue;
            row.clear();
            std::stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            if(!isGlobal()){ //We may want to read all lines
                if(isDiurno()){//Or only daytime or nighttime
                    if(row.at(0).back()!='M'){
                        loadLineInfo(row.at(0)); //ler linha com Code correspondente
                    }
                }
                else{
                    if(row.at(0).back()=='M'){
                        loadLineInfo(row.at(0)); //ler linha com Code correspondente
                    }
                }
            }
            else{
                loadLineInfo(row.at(0)); //ler linha com Code correspondente
            }
        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";
    if(walkValid())loadWalks();

}

void Stcp::setGlobal(bool flag) {global = flag;}
bool Stcp::isGlobal(){return global;}

/**
 * Creates a node for every stop
 */
void Stcp::loadStops() {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file ("dataset/stops.csv", std::ios::in);
    int count = -1;
    if(file.is_open()){
        while(getline(file, line)) {
            count++;
            if (count == 0) continue;
            row.clear();
            std::stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            graph.nodes[count] = Graph::Node{list<Graph::Edge>(),0,0,false, row.at(0), row.at(1), row.at(2), stod(row.at(3)), stod(row.at(4))};
            index.emplace(row.at(0), count);  //Store the code in a map
            indexReverse.emplace(count,row.at(0));
            codeToName.emplace(row.at(0),row.at(1));
        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";
}

/**
 * Creates a new type of graph where there is a node for every combination <stop code, line> and the edges have a pair <change in Lines, change in Stops> as the weight
 */
void Stcp::loadLineGraph(){
    int n = 0;
    for(const auto& node:graph.nodes){
        n += node.adj.size();
        for(const auto& edge:node.adj){
            if(graph.nodes[edge.dest].adj.empty()){
                n++;
            }
        }
    }

    lineGraph = LineGraph(n, true);
    int count = 1;
    for(const auto& node:graph.nodes){
        list<Graph::Edge> edges = node.adj;
        for(const auto& edge:edges){
            lineGraph.nodes[count] = LineGraph::Node{list<LineGraph::Edge>(), make_pair(-1,-1),0,false, node.code, node.name, node.zone,node.latitude,node.longitude ,edge.line};
            multiIndex.emplace(node.code,count); //Store code in a multimap
            specificIndex.emplace(node.code + edge.line, count); //Store code + line in a map
            count++;

            Graph::Node dest = graph.nodes[edge.dest];
            //In case the stop is at the end of a line and has no edges starting from it
            if(dest.adj.empty()){
                lineGraph.nodes[count] = LineGraph::Node{list<LineGraph::Edge>(), make_pair(-1,-1),0,false, dest.code, dest.name, dest.zone,dest.latitude,dest.longitude ,edge.line};
                multiIndex.emplace(dest.code,count);
                specificIndex.emplace(dest.code + edge.line, count);
                count++;
            }

//            LineGraph::Node no = lineGraph.nodes[count];
//            cout << no.code <<", " << no.name << ", " << no.line << endl;

        }
        for(auto i = edges.begin(); i != (--edges.end())++; i++){
            for(auto j = (++i)--; j !=edges.end(); j++){
//                if (i->line == "walk" || j->line == "walk"){continue;}
                lineGraph.addEdge(specificIndex[node.code + i->line] , specificIndex[node.code + j->line], make_pair(1,0));
                lineGraph.addEdge(specificIndex[node.code + j->line] , specificIndex[node.code + i->line], make_pair(1,0)); //num sentido e noutro
//                cout << node.code << ", " << i->line << ", " << j->line << endl;
            }
        }
    }
    //after all nodes have been created we can create edges between any two nodes
    for(const auto& node: graph.nodes){
        for(const auto& edge: node.adj){
            lineGraph.addEdge(specificIndex[node.code + edge.line],specificIndex[graph.nodes[edge.dest].code + edge.line] ,make_pair(0,1));
//            cout << node.code << ", Linha: " <<edge.line << ", " << graph.nodes[edge.dest].code << endl;
        }
    }
}
/**
 * Best distance between two stops
 * @param code1
 * @param code2
 * @return
 */
double Stcp::bestDistance(const string& code1, const string& code2) {
    double distance = graph.dijkstra_distance2(index[code1],index[code2]);
    const list<int> &a = graph.dijkstra_path(index[code1], index[code2]);
    if(a.empty()){ cerr << "No paths found!" << endl << endl; return 0;}
    cout << "Percurso:" << endl;
    cout << "Paragem Inicial:" << codeToName[indexReverse[a.front()]]<< " (" << indexReverse[a.front()] << ") Zona:" << graph.nodes[a.front()].zone << endl;
    for (auto i = a.begin(); i != a.end();  i++){
        if(i==a.begin()){
            continue;
        }
        if(graph.nodes[*i].parentLine == "walk"){
            cout << "Deve caminhar ate a paragem " << codeToName[indexReverse[*i]] << " (" << indexReverse[*i] << ") Zona:" << graph.nodes[*i].zone << endl;
        }
        else{
            cout << "Deve seguir pela linha " << graph.nodes[*i].parentLine << " para a paragem " << codeToName[indexReverse[*i]] << " (" << indexReverse[*i] << ") Zona:" << graph.nodes[*i].zone << endl;
        }
    }
    cout <<"Distancia:" << distance << endl;
    return 0;
}
/**
 * Set the name of the departure stop
 * @param name
 */
void Stcp::setStartName(const string& name) {
    this->startStop.name = name;

}
/**
 * Set the name of the arrival stop
 * @param name
 */
void Stcp::setEndName(const string& name) {
    this->endStop.name = name;

}

/**
 * Set the coordinates of the arrival stop
 * @param name
 */
void Stcp::setEndCoords(double lat, double lon) {
    this->endStop.lat = lat;
    this->endStop.lon = lon;
}

/**
 * Set the code of the arrival stop
 * @param name
 */
void Stcp::setEndCode(const string &code) {
    this->endStop.code = code;
}

/**
 * Set the coordinates of the departure stop
 * @param name
 */
void Stcp::setStartCoords(double lat, double lon) {
    this->startStop.lat = lat;
    this->startStop.lon = lon;
}

/**
 * Set the code of the departure stop
 * @param name
 */
void Stcp::setStartCode(const string &code) {
    this->startStop.code = code;
}

const unordered_map<std::string, int> &Stcp::getIndex() const {
    return index;
}

const unordered_map<std::string, std::string> &Stcp::getCodeToName() const {
    return codeToName;
}


/**
 * Path that minimizes cost by being closest to the initial zone
 * @param code1
 * @param code2
 */
void Stcp::leastZoneChanges(const string &code1, const string &code2) {
    //para já, zona < distancia
    list<int> path = graph.distanceInZones(index[code1], index[code2]);
    if(path.empty()){ cerr << "No paths found!" << endl << endl; return;}
    string recentZone;
    int counter = 0;
    cout << "Percurso:" << endl;
    cout << "Paragem Inicial:" << codeToName[indexReverse[path.front()]]<< " (" << indexReverse[path.front()] << ") Zona:" << graph.nodes[path.front()].zone << endl;

    path.pop_front();
    for(int & stop : path){
        if(recentZone != graph.nodes[stop].zone) {
            recentZone = graph.nodes[stop].zone;
            counter++;
        }
        if(graph.nodes[stop].parentLine == "walk"){
            cout << "Deve caminhar ate a paragem " << codeToName[indexReverse[stop]] << " (" << indexReverse[stop] << ") Zona:" << graph.nodes[stop].zone << endl;
        }
        else{
            cout << "Deve seguir pela linha " << graph.nodes[stop].parentLine << " para a paragem " << codeToName[indexReverse[stop]] << " (" << indexReverse[stop] << ") Zona:" << graph.nodes[stop].zone << endl;
        }

    }
    cout << "Zonas percorridas: " << counter << endl;

}

/**
 * Path that minimizes number of stops (no tie breaker criteria)
 * @param code1
 * @param code2
 */
void Stcp::leastStops(const string &code1, const string &code2) {
    list<int> path = graph.distanceInStops(index[code1], index[code2]);
    if(path.empty()){ cerr << "No paths found!" << endl << endl; return;}
    cout << "Percurso:" << endl;
    cout << "Paragem Inicial:" << codeToName[indexReverse[path.front()]]<< " (" << indexReverse[path.front()] << ") Zona:" << graph.nodes[path.front()].zone << endl;
    int size = path.size();
    path.pop_front();
    for(int & stop : path){
        if(graph.nodes[stop].parentLine == "walk"){
            cout << "Deve caminhar ate a paragem " << codeToName[indexReverse[stop]] << " (" << indexReverse[stop] << ") Zona:" << graph.nodes[stop].zone << endl;
        }
        else{
            cout << "Deve seguir pela linha " << graph.nodes[stop].parentLine << " para a paragem " << codeToName[indexReverse[stop]] << " (" << indexReverse[stop] << ") Zona:" << graph.nodes[stop].zone << endl;
        }
    }
    cout << "Paragens percorridas: " << size << endl;
}

/**
 * Path that minimizes bus changes, minimizes number of stops as tiebrekaer
 * @param code1
 * @param code2
 */
void Stcp::leastLineChanges(const string& code1, const string& code2) {
    vector<pair<list<int>,pair<int,int>>> paths;
    auto range1 = multiIndex.equal_range(code1);
    auto range2 = multiIndex.equal_range(code2);
    for (auto i = range1.first; i != range1.second; i++){
        for(auto j = range2.first; j != range2.second; j++){
            pair<list<int>,pair<int,int>> dijkstra = lineGraph.dijkstra_pathLines(i->second, j->second);
            if(!dijkstra.first.empty()) paths.push_back(dijkstra);
        }
    }
    sort(paths.begin(),paths.end(), [](const pair<list<int>,pair<int,int>>& l1, const pair<list<int>,pair<int,int>>& l2){
        if( l1.second == l2.second){return l1.first.size() < l2.first.size();}
        return l1.second < l2.second;});

    if(paths.empty()){ cerr << "No paths found!" << endl << endl; return;}
    list<int> res = paths.front().first;
    int size = paths.front().second.first;
    auto it = res.begin();
    cout << "Percurso:" << endl;
    cout << "Paragem Inicial:" << lineGraph.nodes[*it].name << " (" << lineGraph.nodes[*it].code << ") Zona:" << lineGraph.nodes[*it].zone << endl;
    it++;
    for(; it != res.end(); it++){
        auto aux = it;
        auto aux2 = it;
        if(++aux == res.end()){break;}
        if(lineGraph.nodes[*aux2].code == lineGraph.nodes[*aux].code ){
            if(lineGraph.nodes[*aux].line == "walk") cout << "Prepare-se para caminhar na paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;

            else cout << "Prepare-se para mudar para a linha " << lineGraph.nodes[*aux].line << " na paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;        }
        else{
            if(lineGraph.nodes[*aux2].line == "walk"){
                cout << "Deve caminhar ate a paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;
            }
            else cout << "Deve seguir pela linha " << lineGraph.nodes[*aux].line << " para a paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;
        }
    }

    cout << "Mudancas de linha: " << size <<endl;
}

/**
 * Path that minimizes number of stops, least bus changes as tiebreaker
 * @param code1
 * @param code2
 */
void Stcp::leastStopsWithLeastLines(const string &code1, const string &code2){
    vector<pair<list<int>,pair<int,int>>> paths;
    auto range1 = multiIndex.equal_range(code1);
    auto range2 = multiIndex.equal_range(code2);
    for (auto i = range1.first; i != range1.second; i++){
        for(auto j = range2.first; j != range2.second; j++){
            pair<list<int>,pair<int,int>> dijkstra = lineGraph.dijkstra_pathStops(i->second, j->second);
            if(!dijkstra.first.empty()) paths.push_back(dijkstra);
        }
    }
    sort(paths.begin(),paths.end(), [](const pair<list<int>,pair<int,int>>& l1, const  pair<list<int>,pair<int,int>>& l2){
        if( l1.second == l2.second){return l1.first.size() < l2.first.size();}
        return l1.second < l2.second;});
    if(paths.empty()){ cerr << "No paths found!" << endl << endl; return;}
    list<int> res = paths.front().first;
    string recentStop;

    auto it = res.begin();
    cout << "Percurso:" << endl;
    cout << "Paragem Inicial:" << lineGraph.nodes[*it].name << " (" << lineGraph.nodes[*it].code << ") Zona:" << lineGraph.nodes[*it].zone << endl;
    it++;
    for(; it != res.end(); it++){
        auto aux = it;
        auto aux2 = it;
        if(++aux == res.end()){break;}
        if(lineGraph.nodes[*aux2].code == lineGraph.nodes[*aux].code ){
            if(lineGraph.nodes[*aux].line == "walk") cout << "Prepare-se para caminhar na paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;

            else cout << "Prepare-se para mudar para a linha " << lineGraph.nodes[*aux].line << " na paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl; }
        else{
            if(lineGraph.nodes[*aux2].line == "walk"){
                cout << "Deve caminhar ate a paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;
            }
            else cout << "Deve seguir pela linha " << lineGraph.nodes[*aux].line << " para a paragem " << lineGraph.nodes[*aux].name << " (" << lineGraph.nodes[*aux].code << ") Zona:" << lineGraph.nodes[*aux].zone << endl;
        }
    }
//    cout << "Paragens percorridas: " << paths.front().second.first <<endl;
}

/**
 * Nearest stops from the indicated coordinates
 * @param latitude
 * @param longitude
 * @param radius
 * @return
 */
std::vector<std::string> Stcp::nearestStop(const double &latitude, const double &longitude, const double &radius) {
    std::vector<std::string> res;
    for(const auto& stop: graph.nodes) {
        if (haversine(latitude, longitude, stop.latitude, stop.longitude) < radius){ //distance in kilometers?
            res.push_back(stop.code);
        }
    }
    return res;
}

/**
 * Add new edges to the graph if the user decides they can also walk a little distance between stops
 */
void Stcp::loadWalks() {
    for(int i = 1; i < graph.nodes.size(); i++){
        for(int j = i + 1 ; j <= graph.nodes.size(); j++){
            double weight = haversine(graph.nodes[i].latitude,graph.nodes[i].longitude,graph.nodes[j].latitude,graph.nodes[j].longitude);
            if(0 < weight && weight < getDistofWalk()){
                if(!hasRoute(i,j)){
                    graph.addEdge(i,j,weight,"walk");
                    graph.addEdge(j,i,weight,"walk"); //Também faz sentido pôr logo ao contrário, certo?
                }
            }
        }
    }
}

/**
 * Checks if there is a direct path between two stops
 * @param i
 * @param j
 * @return
 */
bool Stcp::hasRoute(int i, int j) {
    for(const auto& x : graph.nodes[i].adj){
        if(x.dest == j) return true;
    }
    return false;
}

/**
 * returns the minimum distance that connects all stops
 * @return
 */
double Stcp::globalMST() {
    return graph.kruskal();
}

/**
 * Check if walks are valid
 * @return
 */
bool Stcp::walkValid() const {
    return walk;
}

/**
 * Get the distance that is allowed to walk
 * @return
 */
double Stcp::getDistofWalk() const {
    return dist;
}

/**
 * Set that walks are valid
 */
void Stcp::setWalkValid() {
    this->walk = true;
}

/**
 * Set that walks are invalid
 */
void Stcp::setWalkInvalid() {
    this->walk = false;
}

/**
 * Set distance of walks
 */
void Stcp::setDist(double dist) {
    this->dist = dist;
}

/**
 * Get code of the departure stop
 * @return
 */
std::string Stcp::getStartCode() {
    return this->startStop.code;
}

/**
 * Get code of the arrival stop
 * @return
 */
std::string Stcp::getEndCode() {
    return this->endStop.code;
}

/**
 * Get the departure stop
 * @return
 */
const Stop &Stcp::getStartStop() const {
    return startStop;
}
/**
 * Get the arrival stop
 * @return
 */
const Stop &Stcp::getEndStop() const {
    return endStop;
}

/**
 * Resets the graphs before a load
 */

void Stcp::clear() {
    graph = Graph(numberOfStops,true);
    lineGraph = LineGraph();
    index = std::unordered_map<std::string,int>();
    multiIndex = std::unordered_multimap<std::string,int>();
    specificIndex = std::unordered_map<std::string,int>() ;
    indexReverse = std::unordered_map<int,std::string>() ;
    codeToName = std::unordered_map<std::string,std::string>();
}

/**
 * Select only daytime routes
 */
void Stcp::setDiurno() {this->diurno = true;}

/**
 * Select only nightime routes
 */
void Stcp::setNoturno(){this->diurno = false;}

/**
 * Check if routes are in daytime
 * @return
 */
bool Stcp::isDiurno(){return this->diurno;}

/**
 * Get codes of every stop with a specific name
 * @param name
 * @return
 */
vector<string> Stcp::getCodes(std::string name) {
    vector<string> s;
    for(auto p : this->codeToName){
        if(p.second == name){
            s.push_back(p.first);
        }
    }
    return s;
}










