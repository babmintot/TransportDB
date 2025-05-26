#include "DatabaseManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <limits>

// Загрузка данных из файла
bool DatabaseManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    routes.clear(); // Очищаем текущую базу

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

// Сохранение данных в файл
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

// Добавление новой записи
void DatabaseManager::addRoute() {
    unsigned int number;
    std::string type, departure, arrival;
    float fare;
    unsigned short int hour, minute, second;
    unsigned int stops;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера

    std::cout << "Введите номер рейса: ";
    std::cin >> number;

    std::cin.ignore();
    std::cout << "Введите тип транспорта: ";
    std::getline(std::cin, type);

    std::cout << "Введите стоимость проезда: ";
    std::cin >> fare;

    std::cout << "Введите время в пути (часы минуты секунды): ";
    std::cin >> hour >> minute >> second;

    std::cout << "Введите количество остановок: ";
    std::cin >> stops;

    std::cin.ignore();
    std::cout << "Введите пункт отправления: ";
    std::getline(std::cin, departure);

    std::cout << "Введите пункт прибытия: ";
    std::getline(std::cin, arrival);

    routes.emplace_back(number, type, fare, hour, minute, second, stops, departure, arrival);
    std::cout << "Рейс успешно добавлен.\n";
}

// Удаление записи по номеру
void DatabaseManager::removeRoute() {
    unsigned int number;
    std::cout << "Введите номер рейса для удаления: ";
    std::cin >> number;

    auto it = std::find_if(routes.begin(), routes.end(),
        [number](const Route& r) { return r.routeNumber == number; });

    if (it != routes.end()) {
        routes.erase(it);
        std::cout << "Рейс удален.\n";
    }
    else {
        std::cout << "Рейс с указанным номером не найден.\n";
    }
}

// Просмотр всех записей
void DatabaseManager::displayAllRoutes() const {
    if (routes.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    for (const auto& route : routes) {
        route.display();
    }
}

// Сортировка по номеру рейса
void DatabaseManager::sortRoutesByNumber() {
    std::sort(routes.begin(), routes.end(),
        [](const Route& a, const Route& b) { return a.routeNumber < b.routeNumber; });
    std::cout << "База данных отсортирована по номеру рейса.\n";
}

// Поиск записи по номеру
void DatabaseManager::searchRouteByNumber() {
    unsigned int number;
    std::cout << "Введите номер рейса для поиска: ";
    std::cin >> number;

    auto it = std::find_if(routes.begin(), routes.end(),
        [number](const Route& r) { return r.routeNumber == number; });

    if (it != routes.end()) {
        it->display();
    }
    else {
        std::cout << "Рейс с указанным номером не найден.\n";
    }
}

// Фильтр по диапазону стоимости
void DatabaseManager::filterByFareRange() {
    float minFare, maxFare;
    std::cout << "Введите минимальную стоимость проезда: ";
    std::cin >> minFare;
    std::cout << "Введите максимальную стоимость проезда: ";
    std::cin >> maxFare;

    std::vector<Route> filtered;
    for (const auto& route : routes) {
        if (route.fare >= minFare && route.fare <= maxFare) {
            filtered.push_back(route);
        }
    }

    if (filtered.empty()) {
        std::cout << "Нет рейсов в указанном диапазоне стоимости.\n";
    }
    else {
        std::cout << "Рейсы в указанном диапазоне:\n";
        for (const auto& route : filtered) {
            route.display();
        }
    }
}

// Найти рейс с наименьшим количеством остановок между двумя пунктами
void DatabaseManager::findRouteWithMinStops() {
    std::string departure, arrival;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите пункт отправления: ";
    std::getline(std::cin, departure);
    std::cout << "Введите пункт прибытия: ";
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
        std::cout << "Рейс с наименьшим количеством остановок:\n";
        bestRoute->display();
    }
    else {
        std::cout << "Рейсы между указанными пунктами не найдены.\n";
    }
}

// Перенос рейсов с временем в пути меньше заданного
void DatabaseManager::filterByTravelTime() {
    unsigned short int maxHour, maxMinute, maxSecond;
    std::cout << "Введите максимальное время в пути (часы минуты секунды): ";
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
        std::cout << "Нет рейсов с временем в пути менее заданного значения.\n";
    }
    else {
        std::cout << "Рейсы с временем в пути менее заданного значения:\n";
        filteredDB.displayAllRoutes();

        std::string newFilename = "filtered_database.txt";
        if (filteredDB.saveToFile(newFilename)) {
            std::cout << "Фильтрованная БД сохранена в файл: " << newFilename << "\n";
        }
        else {
            std::cout << "Ошибка при сохранении фильтрованной БД.\n";
        }
    }
}