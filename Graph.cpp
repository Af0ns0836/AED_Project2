#include "Graph.h"

Graph::Graph(int num, bool dir): n(num), hasDir(dir), nodes(num +1) {}

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) {return;}
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) {nodes[dest].adj.push_back({src, weight});}
}

void Graph::bfsPrint(int v) {
    // initialize all nodes as unvisited
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    int i = 1;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front();
        q.pop (); // remove first element of q
        cout << u << ":  " << nodes[u].flight->getSource()->getCode() << " " << nodes[u].flight->getTarget()->getCode() << " " << nodes[u].flight->getAirline()->getCode() << "\n"; // show node order
        if (i == 1) {
            pair<string, int> p;
            p.first = nodes[u].flight->getSource()->getCode();
            p.second = u;
        }
        for (auto e : nodes[u]. adj) {
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true;
            }
        }
        i++;
    }
}

vector<Flight*> Graph::bfsGetVector(int v) {
    // initialize all nodes as unvisited
    for (int v = 1; v <= n; v++) {nodes[v].visited = false;}
    vector<Flight*> vector;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    int i = 1;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front();
        q.pop (); // remove first element of q
        vector.push_back(nodes[u].flight);
        if (i == 1) {
            pair<string, int> p;
            p.first = nodes[u].flight->getSource()->getCode();
            p.second = u;
        }
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true;
            }
        }
        i++;
    }
    return vector;
}

int Graph::connectedComponents() {
    int counter = 0;
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            counter++;
            cout << "connected component: \n";
            bfsPrint(v);
            cout << endl;
        }
    }
    return counter;
}

void Graph::setFlight(int node, Flight* f) {
    nodes[node].flight = f;
}
