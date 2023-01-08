#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "FlightManager.h"

FlightManager::FlightManager(): graphAirports(3019),airports_({}), cities_({}), countries_({}), airlines_({}), flights_(Graph(63832, false)),
                                flightsCity_(Graph(63832, false)){}

void FlightManager::menu() {
    char userchoice;
    bool done = false;
    while (!done) {
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
                        cout << "Indique a sigla do aeroporto de origem:\n"; cin >> local1; cout << '\n';
                        cout << "Faca o mesmo para o aeroporto de destino:\n"; cin >> local2; cout << '\n';
                        cout << "Se pretender, indique as siglas de companhias aereas nas quais pretende voar (digite 'q' quando tiver concluido):\n";
                        while (airline.length() == 3) {
                            airline.clear();
                            cin >> airline;
                            airlines.push_back(airline);
                        }
                        airlines.pop_back();
                        cout << '\n';
                        showPath(local1,local2, airlines);
                        break;
                    }
                    case '2': {
                        cout << "Indique o nome em ingles da cidade de origem:\n";
                        cin.ignore(); getline(cin, local1); cout << "\n";
                        cout << "Faca o mesmo para a cidade de destino:\n";
                        cin.ignore(0); getline(cin, local2);  cout << "\n";
                        cout << "Se pretender, indique as siglas de companhias aereas nas quais pretende voar (digite 'q' quando tiver concluido):\n";
                        while (airline.length() == 3) {
                            airline.clear();
                            cin >> airline;
                            airlines.push_back(airline);
                        }
                        airlines.pop_back();
                        cout << '\n';
                        auto search1 = node_keys_city_.find(local1);
                        list<Flight*> found1 = flightsCity_.bfsGetList((*search1).second);
                        auto search2 = node_keys_city_.find(local2);
                        list<Flight*> found2 = flightsCity_.bfsGetList((*search2).second);
                        unordered_set<string> s1, s2;
                        for (auto f : found1) {s1.insert(f->getSource()->getCode());}
                        for (auto f : found2) {s2.insert(f->getSource()->getCode());}
                        for (const auto& target : s2) {
                            for (const auto& source : s1) {
                                showPath(source, target, airlines);
                            }
                        }
                        break;
                    }
                }
                cout << "\n\n";
                break;
            }
            case '2' : {
                char userchoice2;
                string aeroporto;
                cout << "Introduza a sigla do aeroporto sobre o qual deseja saber as seguintes informacoes:\n"; cin >> aeroporto; cout << "\n";
                cout << "1.Quantos voos existem a partir do aeroporto\n"
                        "2.Quantas companhias aereas operam no aeroporto\n"
                        "3.Quantos destinos diferentes sao atingiveis atraves do aeroporto\n"
                        "4.Quantos aeroportos, cidades ou paises sao atingiveis usando um maximo de Y voos\n\n"
                        "Introduza o que deseja saber: "; cin >> userchoice2; cout << '\n';


                switch (userchoice2) {
                    case '1': {
                        char userchoice3;
                        auto search = node_keys_.find(aeroporto);
                        list<Flight*> found = flights_.bfsGetList((*search).second);
                        cout << "Existem " << found.size() << " voos a partir do aeroporto " << aeroporto << " (1)\n\n";
                        cout << "Caso pretenda uma lista com a informacao, introduza o numero respetivo (caso contrario introduza 0):  "; cin >> userchoice3;
                        cout << '\n';
                        switch (userchoice3) {
                            case '1': {
                                for (Flight* f : found) {
                                    cout << f->getSource()->getCode() << ' ' << f->getTarget()->getCode() << ' ' << f->getAirline()->getCode() << " / Distance = " << f->getSource()->calculateDistance(f->getTarget()) << " km\n";
                                }
                                cout << '\n';
                                break;
                            }
                            case '0': {break;}
                        }
                        break;
                    }
                    case '2': {
                        char userchoice3;
                        auto search = node_keys_.find(aeroporto);
                        list<Flight*> found = flights_.bfsGetList((*search).second);
                        unordered_set<string > s;
                        for (auto f : found) {
                            s.insert(f->getAirline()->getCode());
                        }
                        cout << "Operam " << s.size() << " companhias aereas no aeroporto " << aeroporto << " (1)\n\n";
                        cout << "Caso pretenda uma lista com a informacao, introduza o numero respetivo (caso contrario introduza 0):  "; cin >> userchoice3;
                        cout << '\n';
                        switch (userchoice3) {
                            case '1': {
                                for (const string& a : s) {
                                    cout << a << '\n';
                                }
                                cout << '\n';
                                break;
                            }
                            case '0': {break;}
                        }
                        break;
                    }
                    case '3': {
                        char userchoice3;
                        auto search = node_keys_.find(aeroporto);
                        list<Flight*> found = flights_.bfsGetList((*search).second);
                        unordered_set<string> s1, s2, s3;
                        for (auto f : found) {
                            s1.insert(f->getTarget()->getCode());
                            s2.insert(f->getTarget()->getCity());
                            s3.insert(f->getTarget()->getCountry());
                        }
                        cout << "Da para voar para " << s1.size() << " aeroportos diferentes a partir do aeroporto " << aeroporto << " (1)\n";
                        cout << "Da para voar para " << s2.size() << " cidades diferentes a partir do aeroporto " << aeroporto << " (2)\n";
                        cout << "Da para voar para " << s3.size() << " paises diferentes a partir do aeroporto " << aeroporto << " (3)\n\n";
                        cout << "Caso pretenda uma lista com a informacao, introduza o numero respetivo (caso contrario introduza 0):  "; cin >> userchoice3;
                        cout << '\n';
                        switch (userchoice3) {
                            case '1': {
                                for (const string& a: s1) {
                                    cout << a << '\n';
                                }
                                cout << '\n';
                                break;
                            }
                            case '2': {
                                for (const string& c : s2) {
                                    cout << c << '\n';
                                }
                                cout << '\n';
                                break;
                            }
                            case '3': {
                                for (const string& p : s3) {
                                    cout << p << '\n';
                                }
                                cout << '\n';
                                break;
                            }
                            case '0': {break;}
                        }
                        break;
                    }
                    case '4': {cout << "not working oops :p\n\n";}
                }
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
    int i = 1;
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
        pair<string, int> p; // pair com codigo e indice no grafo connectado
        pair<string, Airport*> p2; // pair com codigo e aeroporto para o outro grafo
        p.first = code;
        p.second = i;
        p2.first = code;
        p2.second = new Airport(code, name, city, country, stod(latitude), stod(longitude));
        Node airport {*new Airport(code, name, city, country, stod(latitude), stod(longitude)),{}};
        graphAirports.addNode(airport,i);
        airports.insert(p);
        airports_.insert(p2);
        cities_.insert(city);
        countries_.insert(country);
        i++;
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
        graphAirports.addEdge(airports[source],airports[target],Flight(a1, a2, a3));
        flights_.addEdge(source_node, target_node);
        flights_.setFlight(target_node, new Flight(a1, a2, a3));
        flightsCity_.addEdge(source_node2, target_node2);
        flightsCity_.setFlight(target_node2, new Flight(a1, a2, a3));
        target_node++;
        target_node2++;
    }
    file.close();
}

void FlightManager::showPath(const string &local1, const string &local2, const vector<string>& airlines) {
    auto search1 = airports.find(local1);
    auto search2 = airports.find(local2);

    if (search1 == airports.end() || search2 == airports.end()){
        cout << "Aeroporto Invalido!" << endl;
        return;
    }

    graphAirports.sortEdges(search1->second);
    graphAirports.sortEdges(search2->second);

    vector<Node> nodes = graphAirports.makePath(search1->second,search2->second, airlines);

    double lastDistance = 0;
    cout << "A procurar uma rota de " << local1 << " -> " << local2 << endl;
    for (size_t i = nodes.size() - 2 ; i != -1 ; i--) {
        cout << "Voo " << nodes[i].distance << ": " << nodes[i].currentFlight.getSource()->getCode() << ", " << nodes[i].currentFlight.getTarget()->getCode() <<
             ", " << nodes[i].currentFlight.getAirline()->getName() << " | " << nodes[i].km - lastDistance << " km\n";

        lastDistance = nodes[i].km;
    }
}
