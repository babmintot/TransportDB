#include <iostream>
#include <windows.h>
#include "DatabaseManager.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); // Включаем UTF-8
    setlocale(LC_ALL, "Russian");

    DatabaseManager db;
    std::string filename = "database.txt";

    if (!db.loadFromFile(filename)) {
        std::cout << "База данных не найдена или пуста.\n";
    }

    int choice;
    do {
        std::cout << "\n=== Меню ===\n";
        std::cout << "1. Просмотреть все записи\n";
        std::cout << "2. Добавить запись\n";
        std::cout << "3. Удалить запись\n";
        std::cout << "4. Сохранить базу\n";
        std::cout << "5. Сортировать по номеру\n";
        std::cout << "6. Поиск по номеру\n";
        std::cout << "7. Фильтр по стоимости\n";
        std::cout << "8. Минимум остановок между пунктами\n";
        std::cout << "9. Фильтр по времени в пути\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите: ";
        std::cin >> choice;

        switch (choice) {
        case 1: db.displayAllRoutes(); break;
        case 2: db.addRoute(); break;
        case 3: db.removeRoute(); break;
        case 4: db.saveToFile(filename); break;
        case 5: db.sortRoutesByNumber(); break;
        case 6: db.searchRouteByNumber(); break;
        case 7: db.filterByFareRange(); break;
        case 8: db.findRouteWithMinStops(); break;
        case 9: db.filterByTravelTime(); break;
        case 0: std::cout << "Выход...\n"; break;
        default: std::cout << "Ошибка ввода\n";
        }

    } while (choice != 0);

    return 0;
}