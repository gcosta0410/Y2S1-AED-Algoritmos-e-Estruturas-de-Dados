#ifndef AED2122_TRABALHO2_LINEGRAPH_H
#define AED2122_TRABALHO2_LINEGRAPH_H

#include "minHeap.h"
#include "disjointSets.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <map>

#define MAX_DISTANCE INT_MAX/2

using namespace std;

class LineGraph {
    friend class Stcp;
    struct Edge {
        int dest;   // Destination node
        pair<int, int> weight; // Pair<line change, stop change>
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        pair<int,int> distance;
        int parent;
        bool visited;

        string code;
        string name;
        string zone;
        double latitude;
        double longitude;
        string line;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    LineGraph(int nodes, bool dir = false);
    LineGraph();

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, pair<int,int> weight = {0,1});
    void dijkstra_linesFirst(int s);
    void dijkstra_stopsFirst(int s);

    pair<list<int>, pair<int, int>> dijkstra_pathLines(int a, int b);
    pair<list<int>, pair<int, int>> dijkstra_pathStops(int a, int b);

};


#endif //AED2122_TRABALHO2_LINEGRAPH_H
