#pragma once
#include <vector>
#include <string>
#include "Route.h"

class DatabaseManager {
private:
    std::vector<Route> routes;

public:
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    void addRoute();
    void removeRoute();
    void displayAllRoutes() const;
    void sortRoutesByNumber();
    void searchRouteByNumber();
    void filterByFareRange();
    void findRouteWithMinStops();
    void filterByTravelTime();
};