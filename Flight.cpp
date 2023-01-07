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
