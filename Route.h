#pragma once
#include "CTime.h"
#include <string>

class Route {
public:
    unsigned int routeNumber;
    std::string transportType;
    float fare;
    CTime travelTime;
    unsigned int numberOfStops;
    std::string departurePoint;
    std::string arrivalPoint;

    Route();
    Route(unsigned int number, const std::string& type, float cost,
        unsigned short int h, unsigned short int m, unsigned short int s,
        unsigned int stops, const std::string& dep, const std::string& arr);

    void display() const;
};