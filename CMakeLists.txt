cmake_minimum_required(VERSION 3.21)
project(AED_Project2)

set(CMAKE_CXX_STANDARD 23)

add_executable(AED_Project2 main.cpp Airport.cpp Airport.h Flight.cpp Flight.h FlightManager.cpp FlightManager.h Airline.cpp Airline.h Graph.cpp Graph.h)
