#include "DatabaseManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <limits>

// �������� ������ �� �����
bool DatabaseManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    routes.clear(); // ������� ������� ����

    unsigned int number;
    std::string type, departure, arrival;
    float fare;
    unsigned short int hour, minute, second;
    unsigned int stops;

    while (file >> number >> type >> fare >> hour >> minute >> second >> stops >> departure >> arrival) {
        routes.emplace_back(number, type, fare, hour, minute, second, stops, departure, arrival);
    }

    file.close();
    return true;
}

// ���������� ������ � ����
bool DatabaseManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& route : routes) {
        file << route.routeNumber << " "
            << route.transportType << " "
            << route.fare << " "
            << route.travelTime.hour << " "
            << route.travelTime.minute << " "
            << route.travelTime.second << " "
            << route.numberOfStops << " "
            << route.departurePoint << " "
            << route.arrivalPoint << "\n";
    }

    file.close();
    return true;
}

// ���������� ����� ������
void DatabaseManager::addRoute() {
    unsigned int number;
    std::string type, departure, arrival;
    float fare;
    unsigned short int hour, minute, second;
    unsigned int stops;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������

    std::cout << "������� ����� �����: ";
    std::cin >> number;

    std::cin.ignore();
    std::cout << "������� ��� ����������: ";
    std::getline(std::cin, type);

    std::cout << "������� ��������� �������: ";
    std::cin >> fare;

    std::cout << "������� ����� � ���� (���� ������ �������): ";
    std::cin >> hour >> minute >> second;

    std::cout << "������� ���������� ���������: ";
    std::cin >> stops;

    std::cin.ignore();
    std::cout << "������� ����� �����������: ";
    std::getline(std::cin, departure);

    std::cout << "������� ����� ��������: ";
    std::getline(std::cin, arrival);

    routes.emplace_back(number, type, fare, hour, minute, second, stops, departure, arrival);
    std::cout << "���� ������� ��������.\n";
}

// �������� ������ �� ������
void DatabaseManager::removeRoute() {
    unsigned int number;
    std::cout << "������� ����� ����� ��� ��������: ";
    std::cin >> number;

    auto it = std::find_if(routes.begin(), routes.end(),
        [number](const Route& r) { return r.routeNumber == number; });

    if (it != routes.end()) {
        routes.erase(it);
        std::cout << "���� ������.\n";
    }
    else {
        std::cout << "���� � ��������� ������� �� ������.\n";
    }
}

// �������� ���� �������
void DatabaseManager::displayAllRoutes() const {
    if (routes.empty()) {
        std::cout << "���� ������ �����.\n";
        return;
    }

    for (const auto& route : routes) {
        route.display();
    }
}

// ���������� �� ������ �����
void DatabaseManager::sortRoutesByNumber() {
    std::sort(routes.begin(), routes.end(),
        [](const Route& a, const Route& b) { return a.routeNumber < b.routeNumber; });
    std::cout << "���� ������ ������������� �� ������ �����.\n";
}

// ����� ������ �� ������
void DatabaseManager::searchRouteByNumber() {
    unsigned int number;
    std::cout << "������� ����� ����� ��� ������: ";
    std::cin >> number;

    auto it = std::find_if(routes.begin(), routes.end(),
        [number](const Route& r) { return r.routeNumber == number; });

    if (it != routes.end()) {
        it->display();
    }
    else {
        std::cout << "���� � ��������� ������� �� ������.\n";
    }
}

// ������ �� ��������� ���������
void DatabaseManager::filterByFareRange() {
    float minFare, maxFare;
    std::cout << "������� ����������� ��������� �������: ";
    std::cin >> minFare;
    std::cout << "������� ������������ ��������� �������: ";
    std::cin >> maxFare;

    std::vector<Route> filtered;
    for (const auto& route : routes) {
        if (route.fare >= minFare && route.fare <= maxFare) {
            filtered.push_back(route);
        }
    }

    if (filtered.empty()) {
        std::cout << "��� ������ � ��������� ��������� ���������.\n";
    }
    else {
        std::cout << "����� � ��������� ���������:\n";
        for (const auto& route : filtered) {
            route.display();
        }
    }
}

// ����� ���� � ���������� ����������� ��������� ����� ����� ��������
void DatabaseManager::findRouteWithMinStops() {
    std::string departure, arrival;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "������� ����� �����������: ";
    std::getline(std::cin, departure);
    std::cout << "������� ����� ��������: ";
    std::getline(std::cin, arrival);

    unsigned int minStops = UINT32_MAX;
    Route* bestRoute = nullptr;

    for (auto& route : routes) {
        if (route.departurePoint == departure && route.arrivalPoint == arrival &&
            route.numberOfStops < minStops) {
            minStops = route.numberOfStops;
            bestRoute = &route;
        }
    }

    if (bestRoute) {
        std::cout << "���� � ���������� ����������� ���������:\n";
        bestRoute->display();
    }
    else {
        std::cout << "����� ����� ���������� �������� �� �������.\n";
    }
}

// ������� ������ � �������� � ���� ������ ���������
void DatabaseManager::filterByTravelTime() {
    unsigned short int maxHour, maxMinute, maxSecond;
    std::cout << "������� ������������ ����� � ���� (���� ������ �������): ";
    std::cin >> maxHour >> maxMinute >> maxSecond;

    DatabaseManager filteredDB;

    for (auto& route : routes) {
        if ((route.travelTime.hour < maxHour) ||
            (route.travelTime.hour == maxHour && route.travelTime.minute < maxMinute) ||
            (route.travelTime.hour == maxHour && route.travelTime.minute == maxMinute &&
                route.travelTime.second <= maxSecond)) {
            filteredDB.routes.push_back(route);
        }
    }

    if (filteredDB.routes.empty()) {
        std::cout << "��� ������ � �������� � ���� ����� ��������� ��������.\n";
    }
    else {
        std::cout << "����� � �������� � ���� ����� ��������� ��������:\n";
        filteredDB.displayAllRoutes();

        std::string newFilename = "filtered_database.txt";
        if (filteredDB.saveToFile(newFilename)) {
            std::cout << "������������� �� ��������� � ����: " << newFilename << "\n";
        }
        else {
            std::cout << "������ ��� ���������� ������������� ��.\n";
        }
    }
}