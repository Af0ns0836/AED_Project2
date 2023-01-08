#ifndef AED_PROJECT2_FLIGHTMANAGER_H
#define AED_PROJECT2_FLIGHTMANAGER_H


#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include "ConnectedGraph.h"
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"
#include "Graph.h"
//! Class that manages everything
/*!
 * This class reads and inserts the data into the specific data structures and also displays the menu
 */

class FlightManager {
    public:
        FlightManager();
        //! Menu function
        /*!
         * This functions has all the call to functions and so on so calculating its complexity is complicated
         */
        void menu();
    //! Function that calls all other read functions
    /*!
     * Time complexity for all 3 functions is the same since they only read from the file and input into the data structures
     * Time complexity - O(n)
     */
        void readFiles(); //! Function that calls all other read functions
        void readAirports(); //! Function that reads the airport data, populates the graph graphAirports, the maps and sets
        void readAirlines(); //! Function that reads the airlines data and inserts on the airlines_ unordered map
        void readFlights(); //! Function that reads the airlines data and populates the graph graphAirports, flights_ and flightsCity_
        void showPath(const string &local1, const string &local2, const vector<string>& airlines);

    private:
        //! All of these maps and sets allow for 0(1) search time.
        unordered_map<string, int> airports; // mapa para o grafo connectado
        unordered_map<string, Airport*> airports_; // mapa para o grafo nao connectado
        unordered_set<string> cities_; //! set that cointains all cities
        unordered_set<string> countries_; //! set that contains all countries
        unordered_map<string, Airline*> airlines_; //! map that contains the airline code and information
        unordered_map<string, int> node_keys_; //! map to store the key of each airport
        unordered_map<string, int> node_keys_city_; //! map to store the key of each city
        Graph flights_, flightsCity_; //! Simpler graph that contains less information
        vector<Flight> flights; //! Vector to store flights
        ConnectedGraph graphAirports; //! More complex graph that contains information from all 3 data files

};


#endif
