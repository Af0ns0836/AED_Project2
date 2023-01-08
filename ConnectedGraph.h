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
        int distance;
    };

//! Connected graph class
/*!
   A class that represents a graph, which each node is an airport
   Each edge has the flight information
   Node:
    airport -> all the airport information
    adjacent -> all the flights from the current airport
    km -> distance in real units(km)
    currentFlight -> current flight from the airport
    distance -> distance in nodes

 */
    class ConnectedGraph {
        vector<Node> nodes;
        int n = 3019;

    public:
        explicit ConnectedGraph(int nodes);
        void addNode(const Node &node, int index);
        void addEdge(int departure, int arrival, Flight flight);
        //! sorts the edges of the node, time complexity O(n)
        void sortEdges(int index);
        //! Breadth-first search that traverses the graph in O(|V| + |E|)
        /*!
         *
         * @param departure integer value that represents the airport position on the graph
         * @param airlines vector that contains all the airlines
         */
        void BFS(int departure, const vector<string>& airlines);
        //! Function that creates a path between the two input locations
        /*!
         * Inside the function its used a BFS to store the path into a vector and then print it
         * Time complexity -> O(|V| + |E|)
         * @param departure postion on the graph for the departure airport
         * @param arrival postion on the graph for the arrival airport
         * @param airlines vector containing all the selected airlines
         */
        vector<Node> makePath(int departure, int arrival, const vector<string>& airlines);
        /*!
         * @param lat1 latitude from location1
         * @param lon1 longitude from location1
         * @param lat2 latitude from location2
         * @param lon2 longitude from location2
         */
        double calculateDistance(double lat1, double lon1, double lat2, double lon2); //! Distance calculation O(1)
    };


#endif
