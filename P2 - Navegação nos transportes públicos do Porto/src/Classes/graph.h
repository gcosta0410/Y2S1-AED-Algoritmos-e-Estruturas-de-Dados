// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include "disjointSets.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

class Graph {
    friend class Stcp;
    int numberOfLines; //inútil de momento
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight

        string line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double distance;
        int parent;
        bool visited;

        string code;
        string name;
        string zone;
        double latitude;
        double longitude;

        string parentLine;
//        int zonesDistance;




    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes,int numberOfLines, bool dir = false);
    Graph(int nodes, bool dir = false);


    Graph();

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight = 1);
    void addEdge(int src, int dest, double weight, const string& lineCode);


    // ----- Functions to implement in this class -----
    int prim(int v);
    double kruskal();

    int dfs(int v);


    // Breadth-First Search: example implementation
    void bfs(int v);
    void bfsD(int v);
    void bfsStops(int v);
    list<int> distanceInStops(int a, int b);


    void dijkstra(int s);
    void dijkstraZones(int s);
    int dijkstra_distance(int a, int b);
    double dijkstra_distance2(int a, int b);
    list<int> dijkstra_path(int a, int b);

    list<int> distanceInZones(int a, int b);
};

#endif
