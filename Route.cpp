#include "Route.h"
#include <iostream>

Route::Route()
    : routeNumber(0), fare(0.0f), numberOfStops(0) {}

Route::Route(unsigned int number, const std::string& type, float cost,
    unsigned short int h, unsigned short int m, unsigned short int s,
    unsigned int stops, const std::string& dep, const std::string& arr)
    : routeNumber(number), transportType(type), fare(cost),
    travelTime(h, m, s), numberOfStops(stops),
    departurePoint(dep), arrivalPoint(arr) {}

void Route::display() const {
    std::cout << "����� �����: " << routeNumber << "\n";
    std::cout << "��� ����������: " << transportType << "\n";
    std::cout << "��������� �������: " << fare << "\n";
    std::cout << "����� � ����: " << travelTime.toString() << "\n";
    std::cout << "���������� ���������: " << numberOfStops << "\n";
    std::cout << "����� �����������: " << departurePoint << "\n";
    std::cout << "����� ��������: " << arrivalPoint << "\n";
    std::cout << "-----------------------------\n";
}