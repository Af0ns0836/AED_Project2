#include "Airline.h"

#include <utility>

Airline::Airline() = default;

Airline::Airline(string  code, string  name, string  callsign, string  country): code_(std::move(code)),
name_(std::move(name)), callsign_(std::move(callsign)), country_(std::move(country)) {}

string Airline::getCode() {
    return code_;
}

string Airline::getName() {
    return name_;
}

string Airline::getCallSign() {
    return callsign_;
}

string Airline::getCountry() {
    return country_;
}
