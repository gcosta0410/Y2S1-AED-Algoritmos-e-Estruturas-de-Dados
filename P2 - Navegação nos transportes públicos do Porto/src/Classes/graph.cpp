// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include <algorithm>
#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}
// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


void Graph::addEdge(int src, int dest, double weight, const string& lineCode) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, lineCode});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, lineCode});
}

Graph::Graph() = default;


int Graph::prim(int r) {
    for (auto& v:nodes) {
        v.distance = INT32_MAX;
        v.parent = -1;
    }
    nodes[r].distance = 0;
    MinHeap<int,double> q(n,-1);
    for(int i = 1; i <= n ; i++){
        q.insert(i,nodes[i].distance);
    }
    double res = 0;
    while(q.getSize() > 0){
        int u = q.removeMin();
        res += nodes[u].distance;
        for(const auto& v: nodes[u].adj){
            if (q.hasKey(v.dest) &&  v.weight < nodes[v.dest].distance){
                nodes[v.dest].parent = u;
                nodes[v.dest].distance = v.weight;
                q.decreaseKey(v.dest, v.weight);
            }
        }
    }
    return res;
}


/**
 * Used to compute an MST for the STCP network.
 * It prevents connections between two stops of the same name (since they are too close).
 * It operates as if the graph is directed by duplicating every edge.
 * @return
 */
double Graph::kruskal() {
    struct E{
        int i;
        int f;
        double w;
    };
    DisjointSets<int> disjSet;
    map<int,set<int>> adjacencies;
    double totalDistance = 0;
    vector<E> edges;
    for (int i = 1; i <= n; i++){
        adjacencies.insert({i,set<int>()});
        for(const auto& e:nodes[i].adj){
//            if(nodes[i].name != nodes[e.dest].name){ //prevents an edge between two stops with the same name
                edges.push_back({i,e.dest, e.weight});
                edges.push_back({e.dest,i, e.weight});  //edge duplication in the opoosite direction
//            }
        }
        disjSet.makeSet(i);
    }
    sort(edges.begin(), edges.end(),[](E e1, E e2){
        return e1.w < e2.w;
    });
    for (auto& edge:edges){
        if(disjSet.find(edge.i) != disjSet.find(edge.f)){
            totalDistance += edge.w;
            disjSet.unite(edge.i, edge.f);
            adjacencies[edge.i].insert(edge.f);
//            cout << nodes[edge.i].name << " -> " << nodes[edge.f].name << endl;
        }
    }

    for(int i = 1; i <= n; i++){
        set<int> adj = adjacencies[i];
        if(!adj.empty()) {
            cout << "A paragem " << nodes[i].name << " ("  << nodes[i].code << ") fica ligada a" << ": ";
            for (auto &node: adj) {
                cout << nodes[node].name << " ("  << nodes[node].code << ")";
                adj.erase(adj.find(node));
                if(!adj.empty()) cout << ", ";
            }
            cout << endl;
        }
    }
    return totalDistance;
}

/**
 * Simple dfs
 * @param v
 * @return
 */
int Graph::dfs(int v) {
    int count = 1;
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            count = count + dfs(w);
    }
    return count;
}

/**
 * Simple bfs
 * @param v
 */
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

void Graph::bfsD(int v) {
    for (int vv=1; vv<=n; vv++) {
        nodes[vv].distance = -1;
        nodes[vv].visited = false;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = 1 + nodes[u].distance;
            }
        }
    }
}

/**
 * O(|E|log|V|)
 * @param v
 */
void Graph::bfsStops(int v) {
    for (int i = 1; i <= n; i++){
        nodes[i].distance = -1;
        nodes[i].visited = false;
        nodes[i].parent = 0;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    nodes[v].parent = v;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
//        cout << u << " "; // show node order
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].parentLine = e.line;
                nodes[w].visited = true;
                nodes[w].distance = 1 + nodes[u].distance;
                nodes[w].parent = u;
                nodes[w].parentLine = e.line;
            }
        }
    }
}

list<int> Graph::distanceInStops(int a, int b){
    list<int> path;
    bfsStops(a);
    if(nodes[b].distance == -1) return path;
    int v = b;
    path.push_front(v);
    while(v!=a){
        v = nodes[v].parent;
        path.push_front(v);
    }
    return path;

}





int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if(nodes[b].distance == INT_MAX/2) return -1;
    return nodes[b].distance;
}
/**
 * O(|E|log|V|)
 * @param a
 * @param b
 * @return
 */
double Graph::dijkstra_distance2(int a, int b) {
    MinHeap<int,double> q(n,-1);
    for (int i = 1; i <= this->n ; i++){
        nodes[i].distance = INT_MAX/2;
        nodes[i].visited = false;
        q.insert(i,INT_MAX/2);
    }
    nodes[a].distance = 0;
    nodes[a].parent = a;
    q.decreaseKey(a,0);
    while(q.getSize()!=0){
        int u = q.removeMin();
        nodes[u].visited = true;
        for(const auto& e : nodes[u].adj){
            int v = e.dest;
            double w = e.weight;
            if(!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].parent = u;
                nodes[v].parentLine = e.line; //
            }
        }
    }
    if(nodes[b].distance == INT_MAX/2) return -1;
    else return nodes[b].distance;
}

// ..............................
// b) Caminho mais curto entre dois nós
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    dijkstra(a);
    if(nodes[b].distance == INT_MAX/2) return path;
    int v = b;
    path.push_front(v);
    while(v!=a){
        v = nodes[v].parent;
        path.push_front(v);
    }
    return path;
}


/**
 * Shortest distance from a node to all others.
 * Used to get the path that passes through the minimum number of stops
 * @param s
 */
void Graph::dijkstra(int s) {
    MinHeap<int,int> q(n, -1);
    for(int v = 1; v <= n; v++){
        nodes[v].distance = INT_MAX/2;
        q.insert(v, INT_MAX/2);
        nodes[v].visited = false;
    }
    nodes[s].distance = 0;
    nodes[s].parent = s;
    q.decreaseKey(s, 0);
    while(q.getSize() > 0){
        int u = q.removeMin();
        nodes[u].visited = true;
        for(const auto& e:nodes[u].adj){
            int v = e.dest;
            int w = e.weight;
            if(!nodes[v].visited && nodes[u].distance + w < nodes[v].distance){
                nodes[v].distance = nodes[u].distance + w;
                nodes[v].parent = u;
                q.decreaseKey(v, nodes[v].distance);
            }
        }
    }
}

/**
 * Shortest zone distance between a stop and all others. Second criteria is the path distance.
 * @param s
 */
void Graph::dijkstraZones(int s) {
    MinHeap<int,pair<int,double>> q(n, -1); // nó -> <mudanças de zona, distancia>
    map<string,int> costToZone; //para cada código de linha, guarda o número de mudanças de linha desde o nó inicial;

    for(int i = 1; i <= n; i++){
        nodes[i].distance = INT_MAX/2;
        nodes[i].visited = false;
//        nodes[i].zonesDistance = INT_MAX/2;
        q.insert(i, {INT_MAX/2, INT_MAX/2});
        costToZone.insert(make_pair(nodes[i].zone, INT_MAX/2));
    }
    nodes[s].distance = 0;
    nodes[s].parent = s;
//    nodes[s].zonesDistance = 0;
    costToZone[nodes[s].zone] = 0;
    q.decreaseKey(s, {0,0});
    while(q.getSize() > 0){
        int u = q.removeMin();
        nodes[u].visited = true;
        string uZone = nodes[u].zone;
        for(const auto& e:nodes[u].adj){
            double w = e.weight;
            int v = e.dest;
            string vZone = nodes[v].zone;

            if(!nodes[v].visited && costToZone[uZone] + 1 < costToZone[vZone]){
                costToZone[vZone] = costToZone[uZone] + 1;
                nodes[v].parent = u;
                nodes[v].parentLine = e.line;
                q.decreaseKey(v, {costToZone[vZone], nodes[v].distance});
            }
            if(!nodes[v].visited && nodes[u].distance + w < nodes[v].distance){
                nodes[v].distance = nodes[u].distance + w;
                nodes[v].parent = u;
                nodes[v].parentLine = e.line;
                q.decreaseKey(v, {costToZone[vZone], nodes[v].distance});
            }
        }
    }
}

/**
 * Returns the path from dijkstraZones
 * @param a
 * @param b
 * @return
 */
list<int> Graph::distanceInZones(int a, int b) {
    list<int> path;
    dijkstraZones(a);
    if(nodes[b].distance == INT_MAX/2) return path;
    int v = b;
    path.push_front(v);
    while(v!=a){
        v = nodes[v].parent;
        path.push_front(v);
    }
    return path;
}





