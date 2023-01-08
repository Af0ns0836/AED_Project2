#include "ConnectedGraph.h"

ConnectedGraph::ConnectedGraph(int nodes) : nodes(nodes + 1) {
}

void ConnectedGraph::clear() {
    for (Node node : nodes) node.adjacent.clear();
    nodes.clear();
}

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

void ConnectedGraph::BFS(int departure) {

    for (int i = 1 ; i < nodes.size() ; i++) {
        nodes[i].visited = false;
        nodes[i].distance = 0;
        nodes[i].parent = i;
        //nodes[i].currentFlight = new Flight {Airport{}};// isto seria o voo atual com a source, target e airline por ordem
        nodes[i].customWeight.km = 0;
    }
    if (!nodes[departure].available) {
        cout << "A origem nao esta disponivel" << endl;
        return;
    }
    queue<int> visitedNodes = {};
    visitedNodes.push(departure);
    nodes[departure].visited = true;
    nodes[departure].distance = 0;
    //nodes[departure].currentFlight.getAirline()->getCode() = " ";
     // isto seria o voo atual com a source, target e airline por ordem
    while (!visitedNodes.empty()) {

        int node = visitedNodes.front();
        visitedNodes.pop();

        if (nodes[node].available) {
            for (const Edge &edge : nodes[node].adjacent) {

                int n = edge.dest;
                double w = edge.weight;

                if (!nodes[n].visited) {
                    visitedNodes.push(n);
                    nodes[n].visited = true;
                    nodes[n].distance = nodes[node].distance + 1;
                    nodes[n].parent = node;
                    nodes[n].currentFlight = edge.flight;
                    nodes[n].customWeight.km = nodes[node].customWeight.km + w;
                }
            }
        }
    }
}
vector<Node> ConnectedGraph::makePath(int departure, int arrival) {

    vector<Node> path = {};

    if (!nodes[departure].available || !nodes[arrival].available) {
        cout << "Partida/Destino nao disponivel" << endl;
        return path;
    }

    BFS(departure);

    if (nodes[arrival].customWeight.km == INF) return path;

    int i = arrival;
    path.push_back(nodes[i]);
    while (i != departure) {
        i = nodes[i].parent;
        path.push_back(nodes[i]);
    }
    return path;
}
Node ConnectedGraph::getNode(Airport* a2) {

    Node result;
    double distance = INT_MAX;
    for (int i = 1 ; i < nodes.size() ; i++) {
        double dis = calculateDistance(nodes[i].airport.getLatitude(), nodes[i].airport.getLongitude(),
                                     a2->getLatitude(), a2->getLongitude());
        if (distance > dis) {
            result = nodes[i];
            distance = dis;
        }
    }
    return result;
}
vector<Node> ConnectedGraph::getNode(const string &city) {

    vector<Node> result;
    for (int i = 1 ; i < nodes.size() ; i++) {

        if (nodes[i].airport.getCity() == city) {
            result.push_back(nodes[i]);
        }
    }
    return result;
}
void ConnectedGraph::activateAirport(int airport) {
    nodes[airport].available = true;
}
void ConnectedGraph::disableAirport(int airport) {
    nodes[airport].available = false;
}
void ConnectedGraph::disableFlight(Flight &flight) {
    for (Node &node : nodes) {
        for (Edge &edge : node.adjacent) {
            if (edge.flight.getSource() == flight.getSource() && edge.flight.getTarget() == flight.getTarget() && edge.flight.getAirline() == flight.getAirline()) node.available = false;
        }
    }
}
void ConnectedGraph::disableAirline(const string &airline) {
    for (Node &node: nodes) {
        if (node.currentFlight.getAirline()->getName() == airline) node.available = false;
    }// aqui nao sei bem se seria o nome mesmo ou o codigo mas pronto
}
void ConnectedGraph::activateAirline(const string &airline) {
    for (Node &node : nodes) {
        if (node.currentFlight.getAirline()->getName() == airline) node.available = true;
    }// aqui nao sei bem se seria o nome mesmo ou o codigo mas pronto
}
void ConnectedGraph::activateAllAirlines() {
    for (Node &node : nodes) {
        node.available = true;
    }
}
void ConnectedGraph::activateAllAirports(){
    for(int i = 1;i<=n;i++) disableAirport(i);
}
void ConnectedGraph::disableAllAirports() {
    for (Node &node : nodes) {
        node.available = false;
    }
}
int ConnectedGraph::countFlightsSourceAirport(string airport) {
    int count = -1;
    for(int i = 1; i <= n; i++)
    {
        if(nodes[i].airport.getCode() == airport)
        {
            count = nodes[i].adjacent.size();
        }
    }
    return count ;
}
int ConnectedGraph::countAirlinesAirport(string airport, string airline){
    int count = 0;
    for(int i = 1; i <= n; i++)
    {
        if(nodes[i].airport.getCode() == airport)
        {
            for(auto edge : nodes[i].adjacent)
            {
                if (edge.flight.getAirline()->getCode() == airline)
                {//mesma coisa deve ser o codigo que isto recebe, idk
                    count++;
                }
            }
        }
    }
    return count ;
}
int ConnectedGraph::countTargetsAirport(string airport){
    set<string> visited;
    for(int i = 1; i <= n; i++){

        if(nodes[i].airport.getCode() == airport){

            for(auto edge : nodes[i].adjacent) {
                visited.insert(edge.flight.getTarget()->getCode());
                activateAirport(edge.dest);
            }
        }
    }
    return visited.size();
}
set<string> ConnectedGraph::retTargetsAirport(string airport){
    set<string> visited;
    for(int i = 1; i <= n; i++)
    {
        if(nodes[i].airport.getCode() == airport)
        {
            for(auto edge : nodes[i].adjacent){
                visited.insert(edge.flight.getTarget()->getCode());
                activateAirport(edge.dest);
            }
        }
    }
    return visited;
}
int ConnectedGraph::countCityTargetsAirport(string airport){
    set<string> visited;
    for(int i = 1; i <= n; i++)
    {
        if(nodes[i].airport.getCode() == airport)
        {
            for(auto edge: nodes[i].adjacent){
                visited.insert(nodes[edge.dest].airport.getCity());
            }
        }
    }
    return visited.size();
}
int ConnectedGraph::countCountryTargetsAirport(string airport){
    set<string> visited;
    for(int i = 1; i <= n; i++)
    {
        if(nodes[i].airport.getCode() == airport)
        {
            for(auto edge: nodes[i].adjacent){
                visited.insert(nodes[edge.dest].airport.getCountry());
            }
        }
    }
    return visited.size();
}
int ConnectedGraph::airportsReached(string airport, int flightsNum){

    for(int i = 1; i<=n ; i++)
    {
        if (nodes[i].airport.getCode() == airport)
        {
            activateAirport(i);
        }
    }

    if(flightsNum < 2) return countTargetsAirport(airport);
    for(int i = 0; i < flightsNum ; i++)
    {
        vector<Node> newNodes =nodes;
        for(int i = 1; i<=n;i++) {
            if (nodes[i].available) {
                for(Edge edge: nodes[i].adjacent) {
                    newNodes[edge.dest].available = true;
                }
            }
        }
        nodes = newNodes;
    }

    int count = 0;
    for(Node node: nodes){
        if(node.available) {
            count++;
        }
    }
    return count;
}
int ConnectedGraph::citiesReached(string airport, int flightsNum){
    set<string> visited;

    if(flightsNum < 2) return countCityTargetsAirport(airport);

    for(Node node: nodes){
        if(node.available) {
            visited.insert(node.airport.getCity());
        }
    }
    return visited.size();

}
int ConnectedGraph::countriesReached(string airport, int flightsNum){
    set<string> visited;

    if(flightsNum < 2) return countCountryTargetsAirport(airport);

    for(Node node: nodes){
        if(node.available) {
            visited.insert(node.airport.getCountry());
        }
    }
    return visited.size();
}
