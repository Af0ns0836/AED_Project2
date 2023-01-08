#ifndef AED_PROJECT2_GRAPH_H
#define AED_PROJECT2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "Flight.h"
using namespace std;


//! Simpler graph that is grouped either by airport or city
/*!
 * This graph is used for task number 2
 * Edge:
 *  dest -> Destination node
 *  weight -> An integer weight
 * Node:
 *  adj -> The list of outgoing edges (to adjacent nodes)
 *  visited -> flag to check if the node has been visited
 *  flight -> Flight object to store flight information
 */
class Graph {
    struct Edge {
            int dest;
            int weight;
    };
    struct Node {
        list<Edge> adj;
        bool visited;
        Flight* flight;
    };

public:
    //! Constructor: nr nodes and direction (default: directed)
    explicit Graph(int nodes, bool dir = true);
    //! Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);
    void setFlight(int node, Flight* f);
    list<Flight *> bfsGetList(int v); //! Bfs that returns a list of flights. Time complexity - O(V + E)

private:
    int n;
    bool hasDir; // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
};


#endif
