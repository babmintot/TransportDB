#pragma once
#include <string>

struct CTime {
    unsigned short int hour;
    unsigned short int minute;
    unsigned short int second;

    CTime();
    CTime(unsigned short int h, unsigned short int m, unsigned short int s);
    std::string toString() const;
};