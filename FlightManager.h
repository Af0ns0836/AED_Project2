#ifndef AED_PROJECT2_FLIGHTMANAGER_H
#define AED_PROJECT2_FLIGHTMANAGER_H


#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include "Graph.h"
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

class FlightManager {
    public:
        FlightManager();
        void menu();
        void readFiles();
        void readAirports();
        void readAirlines();
        void readFlights();
        void findFlightRoutes(const string& SourceAirportCode, const string& TargetAirportCode, const vector<string>& airlines);
        void findFlightRoutesCity(const string& SourceAirportCity, const string& TargetAirportCity, const vector<string>& airlines);
        void sortDirectFlights(list<Flight*> &l);
        void sortFlights(list<vector<Flight*>> &l);
        double getScaleDistance(const vector<Flight*>& v);


    private:
        unordered_map<string, Airport*> airports_;
        unordered_set<string> cities_;
        unordered_set<string> countries_;
        unordered_map<string, Airline*> airlines_;
        unordered_map<string, int> node_keys_;
        unordered_map<string, int> node_keys_city_;
        Graph flights_, flightsCity_;
};


#endif
