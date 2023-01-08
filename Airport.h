#ifndef AED_PROJECT2_AIRPORT_H
#define AED_PROJECT2_AIRPORT_H


#include <string>
using namespace std;

//! Airport class
/*!
   A class that contains everthing about an airport, the code, name, city, country, and its coordinates
 */

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
        //! Function that calculates de distance
        /*!
          It receives an airport and calculate the distance beetween the two
          Time complexity - O(1);
        */
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
