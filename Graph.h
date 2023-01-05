#ifndef AED_PROJECT2_GRAPH_H
#define AED_PROJECT2_GRAPH_H


#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "Flight.h"
using namespace std;

class Graph {
    struct Edge {
        int dest; // Destination node
        int weight; // An integer weight
    };
    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;
        Flight* flight;
    };

    public:
        // Constructor: nr nodes and direction (default: undirected)
        explicit Graph(int nodes, bool dir = false);
        // Add edge from source to destination with a certain weight
        void addEdge(int src, int dest, int weight = 1);
        void setFlight(int node, Flight* f);
        vector<string> dfs(int v,string partida,string destino);
        list<Flight *> bfsGetList(int v);

    private:
        vector<string> scales;
        int n; // Graph size (vertices are numbered from 1 to n)
        bool hasDir; // false: undirect; true: directed
        vector<Node> nodes; // The list of nodes being represented
};


#endif
