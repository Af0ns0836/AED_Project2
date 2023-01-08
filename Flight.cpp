#include "Flight.h"

Flight::Flight() = default;

Flight::Flight(Airport *source, Airport *target, Airline *airline): source_(source), target_(target), airline_(airline) {}

Airport * Flight::getSource(){
    return source_;
}

Airport* Flight::getTarget() {
    return target_;
}

Airline* Flight::getAirline() {
    return airline_;
}

void Flight::setSource(Airport *source) {
    source_ = source;
}

void Flight::setAirline(Airline *airline) {
    airline_ = airline;
}

void Flight::setTarget(Airport *target) {
    target_ = target;
}

