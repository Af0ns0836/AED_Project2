#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "FlightManager.h"

FlightManager::FlightManager(): airports_({}), cities_({}), countries_({}), airlines_({}), flights_(Graph(63832, false)),
                                flightsCity_(Graph(63832, false)) {}

void FlightManager::menu() {
    char userchoice;
    bool done = false;
    while(!done){
        cout << "==================================== \n";
        cout << "\t\tMENU \t \n";
        cout << "==================================== \n";
        cout << "1.Pesquisa de voos\n";
        cout << "2.Informacoes sobre um determinado aeroporto\n";
        cout << "Introduza o respetivo numero ou 'q/Q' para terminar: ";
        cin >> userchoice; cout << '\n';
        switch (userchoice) {
            case 'q': done = true;
                break;
            case 'Q': done = true;
                break;
            case '1' : {
                char userchoice2;
                string local1;
                string local2;
                vector<string> airlines;
                string airline = "...";
                cout << "1.Aeroporto -> Aeroporto (sigla)\n";
                cout << "2.Cidade -> Cidade\n";
                cout << "Escolha o formato de pesquisa que pretende:  "; cin >> userchoice2; cout << "\n";
                switch (userchoice2) {
                    case '1': {
                        cout << "Indique a sigla do aeroporto de origem:  "; cin >> local1; cout << "\n";
                        cout << "Faca o mesmo para o aeroporto de destino:  "; cin >> local2; cout << '\n';
                        cout << "Se pretender, indique as siglas de companhias aereas nas quais pretende voar (digite 'q' quando tiver concluido):  ";
                        while (airline.length() == 3) {
                            airline.clear();
                            cin >> airline;
                            airlines.push_back(airline);
                        }
                        airlines.pop_back();
                        cout << '\n';
                        findFlightRoutes(local1, local2, airlines);
                        break;
                    }
                    case '2': {
                        cout << "Indique o nome em ingles da cidade de origem:  "; cin >> local1; cout << "\n";
                        cout << "Faca o mesmo para a cidade de destino:  "; cin >> local2; cout << '\n';
                        cout << "Se pretender, indique as siglas de companhias aereas nas quais pretende voar (digite 'q' quando tiver concluido):  ";
                        while (airline.length() == 3) {
                            airline.clear();
                            cin >> airline;
                            airlines.push_back(airline);
                        }
                        airlines.pop_back();
                        cout << '\n';
                        findFlightRoutesCity(local1, local2, airlines);
                        break;
                    }
                }
                cout << "\n\n";
                break;
            }
            case '2' : {
                string aeroporto;
                int info;
                cout << "Introduza o aeroporto que deseja saber as seguintes informacoes: "; cin >> aeroporto; cout << "\n";
                cout << "1.Quantos voos existem\n"
                        "2.Voos das companhias aereas\n"
                        "3.Os destinos desse aeroporto\n"
                        "4.Paises diferentes\n"
                        "5.Quantos aeroportos, cidades ou paises sao atingiveis usando um maximo de Y voos\n"
                        "Introduza o numero sobre o que deseja saber: "; cin >> info;
                //menuOption2();
                break;
            }

        }
    }
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
    string current_source = "GKA", current_city = "Goroka";
    int source_node = 1, target_node = 1;
    int source_node2 = 1, target_node2 = 1;
    pair<string, int> p, p2;
    p.first = "GKA";
    p.second = 1;
    node_keys_.insert(p);
    p2.first = "Goroka";
    p2.second = 1;
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

        if (current_city != a1->getCity()) {
            current_city = a1->getCity();
            source_node2 = target_node2;
            p2.first = current_city;
            p2.second = source_node2;
            node_keys_city_.insert(p2);
        }

        flights_.addEdge(source_node, target_node);
        flights_.setFlight(target_node, new Flight(a1, a2, a3));
        flightsCity_.addEdge(source_node2, target_node2);
        flightsCity_.setFlight(target_node2, new Flight(a1, a2, a3));
        target_node++;
        target_node2++;
    }
    file.close();
}

void FlightManager::findFlightRoutes(const string& SourceAirportCode, const string& TargetAirportCode, const vector<string>& airlines) {
    auto search = node_keys_.find(SourceAirportCode);
    list<Flight*> found = flights_.bfsGetList((*search).second);
    list<Flight*> copy = found;
    found.remove_if([TargetAirportCode](Flight* f){
        return f->getTarget()->getCode() != TargetAirportCode;
    });
    cout << "Voos diretos:\n";
    if (!airlines.empty()) {
        for (Flight* f : found) {
            for (const auto& a : airlines) {
                if (a == f->getAirline()->getCode()) {
                    cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " / Distance = " << f->getSource()->calculateDistance(f->getTarget()) << " km\n";
                }
            }
        }
        return;
    }
    for (Flight* f : found) {
        cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " / Distance = " << f->getSource()->calculateDistance(f->getTarget()) << " km\n";
    }
    if (found.empty()) {
        list<vector<Flight*>> scales;
        cout << "\nVoos com 1 escala:\n";
        for (Flight* f : copy) {
            auto search2 = node_keys_.find(f->getTarget()->getCode());
            list<Flight*> found2 = flights_.bfsGetList((*search2).second);
            found2.remove_if([TargetAirportCode](Flight* f){
                return f->getTarget()->getCode() != TargetAirportCode;
            });
            for (Flight* f2 : found2) {
                vector<Flight*> v;
                v.push_back(f);
                v.push_back(f2);
                scales.push_back(v);
            }
        }
        sortFlights(scales);
        if (!airlines.empty()) {
            for (const auto& v : scales) {
                int count = 0;
                for (auto f : v) {
                    for (const auto& a : airlines) {
                        if (a == f->getAirline()->getCode()) {
                            count++;
                        }
                    }
                    if (count == v.size()) {
                        vector<Flight*> copy = v;
                        for (auto f : copy) {
                            cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " -> ";
                        }
                        cout << " / " << getScaleDistance(v) << " km\n";
                    }
                }
            }
            return;
        }
        for (const auto& v : scales) {
            for (auto f : v) {
                cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " -> ";
            }
            cout << " / " << getScaleDistance(v) << " km\n";
        }
    }
}

void FlightManager::findFlightRoutesCity(const string& SourceAirportCity, const string& TargetAirportCity, const vector<string>& airlines) {
    auto search = node_keys_city_.find(SourceAirportCity);
    list<Flight*> found = flightsCity_.bfsGetList((*search).second);
    list<Flight*> copy = found;
    found.remove_if([TargetAirportCity](Flight* f){
        return f->getTarget()->getCity() != TargetAirportCity;
    });
    cout << "Voos diretos:\n";
    if (!airlines.empty()) {
        for (Flight* f : found) {
            for (const auto& a : airlines) {
                if (a == f->getAirline()->getCode()) {
                    cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " / Distance = " << f->getSource()->calculateDistance(f->getTarget()) << " km\n";
                }
            }
        }
        return;
    }
    for (Flight* f : found) {
        cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " / Distance = " << f->getSource()->calculateDistance(f->getTarget()) << " km\n";
    }
    if (found.empty()) {
        list<vector<Flight*>> scales;
        cout << "\nVoos com 1 escala:\n";
        for (Flight* f : copy) {
            auto search2 = node_keys_city_.find(f->getTarget()->getCity());
            list<Flight*> found2 = flightsCity_.bfsGetList((*search2).second);
            found2.remove_if([TargetAirportCity](Flight* f){
                return f->getTarget()->getCity() != TargetAirportCity;
            });
            for (Flight* f2 : found2) {
                vector<Flight*> v;
                v.push_back(f);
                v.push_back(f2);
                scales.push_back(v);
            }
        }
        sortFlights(scales);
        if (!airlines.empty()) {
            for (const auto& v : scales) {
                int count = 0;
                for (auto f : v) {
                    for (const auto& a : airlines) {
                        if (a == f->getAirline()->getCode()) {
                            count++;
                        }
                    }
                    if (count == v.size()) {
                        vector<Flight*> copy = v;
                        for (auto f : copy) {
                            cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " -> ";
                        }
                        cout << " / " << getScaleDistance(v) << " km\n";
                    }
                }
            }
            return;
        }
        for (const auto& v : scales) {
            for (auto f : v) {
                cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " -> ";
            }
            cout << " / " << getScaleDistance(v) << " km\n";
        }
    }
}

void FlightManager::sortFlights(list<vector<Flight*>> &l) {
    l.sort([this](const vector<Flight*>& v1, const vector<Flight*>& v2){
        return getScaleDistance(v1) < getScaleDistance(v2);
    });
}

double FlightManager::getScaleDistance(const vector<Flight*>& v) {
    double result = 0;
    for (auto f : v) {
        result += f->getSource()->calculateDistance(f->getTarget());
    }
    return result;
}

void FlightManager::menuOption1(const string& local1, const string& local2, const vector<string>& airlines) {
    findFlightRoutesCity(local1, local2, airlines);
}
