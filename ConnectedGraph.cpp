#include "ConnectedGraph.h"


ConnectedGraph::ConnectedGraph(int nodes) : nodes(nodes + 1) {}

double ConnectedGraph::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void ConnectedGraph::addNode(const Node &node, int index) {
    this->nodes[index] = node;
}

void ConnectedGraph::addEdge(int departure, int arrival, Flight flight) {
    if (departure < 1 || arrival > nodes.size() || departure > nodes.size() || arrival < 1) return;
    nodes[departure].adjacent.push_back({arrival, calculateDistance(nodes[departure].airport.getLatitude(),
                                                                  nodes[departure].airport.getLongitude(),
                                                                  nodes[arrival].airport.getLatitude(),
                                                                  nodes[arrival].airport.getLongitude()), flight});
}

Node ConnectedGraph::getNode(int index) {
    return nodes[index];
}

void ConnectedGraph::sortEdges(int index) {
    nodes[index].adjacent.sort([](Edge e1, Edge e2){
        return e1.weight < e2.weight;
    });
}

void ConnectedGraph::BFS(int departure, const vector<string>& airlines) {
    for (int i = 1 ; i < nodes.size() ; i++) {
        nodes[i].visited = false;
        nodes[i].distance = 0;
        nodes[i].parent = i;
        nodes[i].km = 0;
    }

    queue<int> visitedNodes = {};
    visitedNodes.push(departure);
    nodes[departure].visited = true;
    nodes[departure].distance = 0;
    while (!visitedNodes.empty()) {

        int node = visitedNodes.front();
        visitedNodes.pop();

        for (const Edge &edge : nodes[node].adjacent) {
            int n = edge.dest;
            double w = edge.weight;
            Flight f = edge.flight;

            if (!airlines.empty()) {
                bool check = false;
                for (const string& s: airlines) {
                    if (s != f.getAirline()->getCode()) {
                        continue;
                    } else {check = true;
                        break;}
                }
                if (!check) {continue;}
            }

            if (!nodes[n].visited) {
                visitedNodes.push(n);
                nodes[n].visited = true;
                nodes[n].distance = nodes[node].distance + 1;
                nodes[n].parent = node;
                nodes[n].currentFlight = edge.flight;
                nodes[n].km = nodes[node].km + w;
            }
        }
    }
}
vector<Node> ConnectedGraph::makePath(int departure, int arrival, const vector<string>& airlines) {
    vector<Node> path = {};

    BFS(departure, airlines);

    if (nodes[arrival].km == INF) return path;

    int i = arrival;
    path.push_back(nodes[i]);
    while (i != departure) {
        i = nodes[i].parent;
        path.push_back(nodes[i]);
    }
    return path;
}
