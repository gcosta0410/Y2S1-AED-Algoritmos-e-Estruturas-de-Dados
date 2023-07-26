#include "LineGraph.h"
#include <algorithm>
#include "graph.h"


// Constructor: nr nodes and direction (default: undirected)

LineGraph::LineGraph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}
// Add edge from source to destination with a certain weight
void LineGraph::addEdge(int src, int dest, pair<int,int> weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

LineGraph::LineGraph() = default;

/**
 * Djikstra algorithm where the weight is a pair<change in Lines, change in Stops>
 * @param s
 */
void LineGraph::dijkstra_linesFirst(int s) {
    MinHeap<int,pair<int,int>> q(n, -1);
    for(int v = 1; v <= n; v++){
        nodes[v].distance = {MAX_DISTANCE, MAX_DISTANCE};
        q.insert(v, {MAX_DISTANCE, MAX_DISTANCE});
        nodes[v].visited = false;
    }
    nodes[s].distance = {0,0};
    nodes[s].parent = s;
    q.decreaseKey(s, {0,0});
    while(q.getSize() > 0){
        int u = q.removeMin();
        nodes[u].visited = true;
        for(const auto& e:nodes[u].adj){
            int v = e.dest;
            pair<int,int> w = e.weight;
            if(!nodes[v].visited && make_pair(w.first + nodes[u].distance.first,w.second + nodes[u].distance.second) < nodes[v].distance ){
//                cout << w.first << ", " << w.second << endl;
                nodes[v].distance = {nodes[u].distance.first + w.first, nodes[u].distance.second + w.second };
                nodes[v].parent = u;
                q.decreaseKey(v, nodes[v].distance);
            }
        }
    }
}

/**
 * Djikstra algorithm where the weight is a pair<change in Stops, change in Lines>
 * @param s
 */
void LineGraph::dijkstra_stopsFirst(int s) {
    MinHeap<int,pair<int,int>> q(n, -1);
    for(int v = 1; v <= n; v++){
        nodes[v].distance = {MAX_DISTANCE, MAX_DISTANCE};
        q.insert(v, {MAX_DISTANCE, MAX_DISTANCE});
        nodes[v].visited = false;
    }
    nodes[s].distance = {0,0};
    nodes[s].parent = s;
    q.decreaseKey(s, {0,0});
    while(q.getSize() > 0){
        int u = q.removeMin();
        nodes[u].visited = true;
        for(const auto& e:nodes[u].adj){
            int v = e.dest;
            pair<int,int> w = e.weight;
            if(!nodes[v].visited && make_pair(w.second + nodes[u].distance.first,w.first + nodes[u].distance.second) < nodes[v].distance){
//                cout << w.first << ", " << w.second << endl;
                nodes[v].distance = {nodes[u].distance.first + w.second, nodes[u].distance.second + w.first };
                nodes[v].parent = u;
                q.decreaseKey(v, nodes[v].distance);
            }
        }
    }
}

/**
 * Creates a path from dijkstra_linesFirst
 * @param a
 * @param b
 * @return
 */
pair<list<int>, pair<int, int>> LineGraph::dijkstra_pathLines(int a, int b) {
    list<int> path;
    dijkstra_linesFirst(a);
    if(nodes[b].distance == make_pair(MAX_DISTANCE, MAX_DISTANCE)) return {path,{0,0}};
    int v = b;
    path.push_front(v);
    while(v!=a){
        v = nodes[v].parent;
        path.push_front(v);
    }
    return {path,{nodes[b].distance.first, nodes[b].distance.second + 1} };
}

/**
 * Creates a path from dijkstra_stopsFirst
 * @param a
 * @param b
 * @return
 */
pair<list<int>, pair<int, int>> LineGraph::dijkstra_pathStops(int a, int b) {
    list<int> path;
    dijkstra_stopsFirst(a);
    if(nodes[b].distance == make_pair(MAX_DISTANCE, MAX_DISTANCE)) return {path,{0,0}};
    int v = b;
    path.push_front(v);
    while(v!=a){
        v = nodes[v].parent;
        path.push_front(v);
    }
    pair<int,int> res = nodes[b].distance;
//    return {path,{nodes[b].distance.first, nodes[b].distance.second}};

    return {path,{nodes[b].distance.first + 1, nodes[b].distance.second}};
}


