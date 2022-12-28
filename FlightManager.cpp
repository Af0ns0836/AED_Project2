#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "FlightManager.h"

FlightManager::FlightManager(): airports_({}), cities_({}), countries_({}), airlines_({}), flights_(Graph(63832, false)) {}

void FlightManager::menu() {
    findFlightRoutes("JFK", "CDG");
}

void FlightManager::readFiles() {
    readAirports();
    readAirlines();
    readFlights();
}

void FlightManager::readAirports() {
    ifstream file("../data/airports.csv");
    if(!file) {
        cout << "Error opening file. " << endl;
    }
    file.ignore(150, '\n');
    vector<string> row;
    string line, word;
    while (file.peek() != EOF) {
        row.clear();
        string code, name, city, country, latitude, longitude;
        getline(file, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        code = row[0];
        name = row[1];
        city = row[2];
        country = row[3];
        latitude = row[4];
        longitude = row[5];
        pair<string, Airport*> p;
        p.first = code;
        p.second = new Airport(code, name, city, country, stod(latitude), stod(longitude));
        airports_.insert(p);
        cities_.insert(city);
        countries_.insert(country);
    }
    file.close();
}

void FlightManager::readAirlines() {
    ifstream file("../data/airlines.csv");
    if(!file) {
        cout << "Error opening file. " << endl;
    }
    file.ignore(150, '\n');
    vector<string> row;
    string line, word;
    while (file.peek() != EOF) {
        row.clear();
        string code, name, callsign, country;
        getline(file, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        code = row[0];
        name = row[1];
        callsign = row[2];
        country = row[3];
        pair<string, Airline*> p;
        p.first = code;
        p.second = new Airline(code, name, callsign, country);
        airlines_.insert(p);
    }
    file.close();
}

void FlightManager::readFlights() {
    ifstream file("../data/flights.csv");
    if(!file) {
        cout << "Error opening file. " << endl;
    }
    file.ignore(150, '\n');
    string current_source = "GKA";
    int source_node = 1, target_node = 1;
    pair<string, int> p;
    p.first = "GKA";
    p.second = 1;
    node_keys_.insert(p);
    vector<string> row;
    string line, word;
    while (file.peek() != EOF) {
        row.clear();
        string source, target, airline;
        getline(file, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        source = row[0];
        target = row[1];
        airline = row[2];

        if (current_source != source) {
            current_source = source;
            source_node = target_node;
            p.first = current_source;
            p.second = source_node;
            node_keys_.insert(p);
        }

        Airport* a1 = airports_.find(source)->second;
        Airport* a2 = airports_.find(target)->second;
        Airline* a3 = airlines_.find(airline)->second;

        flights_.addEdge(source_node, target_node);
        flights_.setFlight(target_node, new Flight(a1, a2, a3));
        target_node++;
    }
    file.close();
}

void FlightManager::findFlightRoutes(const string& SourceAirportCode, const string& TargetAirportCode) {
    auto search = node_keys_.find(SourceAirportCode);
    vector<Flight*> found = flights_.bfsGetVector((*search).second);
    for (auto f : found) {
        bool check = f->getTarget()->getCode() == TargetAirportCode;
        if (check) cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << '\n';
    }
}
