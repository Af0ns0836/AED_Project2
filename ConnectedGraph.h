#ifndef AED_PROJECT2_CONNECTEDGRAPH_H
#define AED_PROJECT2_CONNECTEDGRAPH_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <queue>
#include "Airport.h"
#include "Flight.h"

using namespace std;

#define INF (INT_MAX/2)

    struct Edge {
        int dest;
        double weight;
        Flight flight;
    };

    struct Node {
        Airport airport;
        list<Edge> adjacent;
        double km;
        bool visited;
        int parent;
        Flight currentFlight;
        int distance; //in nodes
    };

    class ConnectedGraph {
        vector<Node> nodes;
        int n = 3019;

    public:
        explicit ConnectedGraph(int nodes);
        void addNode(const Node &node, int index);
        void addEdge(int departure, int arrival, Flight flight);
        Node getNode(int index);
        void sortEdges(int index);
        void BFS(int departure, const vector<string>& airlines);
        vector<Node> makePath(int departure, int arrival, const vector<string>& airlines);
        double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    };


#endif
