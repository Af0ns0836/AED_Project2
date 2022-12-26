#include "Airport.h"

#include <utility>
#include <cmath>

Airport::Airport(): latitude_(0.0), longitude_(0.0) {}

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude):
code_(std::move(code)), name_(std::move(name)), city_(std::move(city)), country_(std::move(country)),
latitude_(latitude), longitude_(longitude) {}

string Airport::getCode() {
    return code_;
}

string Airport::getName() {
    return name_;
}

string Airport::getCity() {
    return city_;
}

string Airport::getCountry() {
    return country_;
}

double Airport::getLatitude() const {
    return latitude_;
}

double Airport::getLongitude() const {
    return longitude_;
}

double Airport::calculateDistance(const Airport& a2) const {
    double dLat = (a2.getLatitude() - this->getLatitude()) * M_PI / 180.0;
    double dLon = (a2.getLongitude() - this->getLongitude()) * M_PI / 180.0;

    // convert to radians
    double lat1Rad = this->getLatitude() * M_PI / 180.0;
    double lat2Rad = a2.getLatitude() * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1Rad) * cos(lat2Rad);
    double rad = 6371.0;
    double c = 2.0 * asin(sqrt(a));
    return rad * c;
}
