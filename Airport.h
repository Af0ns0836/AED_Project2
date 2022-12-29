#ifndef AED_PROJECT2_AIRPORT_H
#define AED_PROJECT2_AIRPORT_H


#include <string>
using namespace std;

class Airport {
    public:
        Airport();
        explicit Airport(string code); //for searching only
        Airport(string code, string  name, string  city, string  country, float latitude, float longitude);
        string getCode() const;
        string getName();
        string getCity();
        string getCountry();
        double getLatitude() const;
        double getLongitude() const;
        double calculateDistance(Airport* a2) const;

    private:
        string code_;
        string name_;
        string city_;
        string country_;
        float latitude_;
        float longitude_;
};


#endif
