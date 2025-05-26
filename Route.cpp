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
    std::cout << "Номер рейса: " << routeNumber << "\n";
    std::cout << "Тип транспорта: " << transportType << "\n";
    std::cout << "Стоимость проезда: " << fare << "\n";
    std::cout << "Время в пути: " << travelTime.toString() << "\n";
    std::cout << "Количество остановок: " << numberOfStops << "\n";
    std::cout << "Пункт отправления: " << departurePoint << "\n";
    std::cout << "Пункт прибытия: " << arrivalPoint << "\n";
    std::cout << "-----------------------------\n";
}