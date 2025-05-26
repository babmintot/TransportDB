#include "CTime.h"
#include <sstream>

CTime::CTime() : hour(0), minute(0), second(0) {}

CTime::CTime(unsigned short int h, unsigned short int m, unsigned short int s)
    : hour(h), minute(m), second(s) {}

std::string CTime::toString() const {
    std::ostringstream oss;
    oss << hour << ":" << minute << ":" << second;
    return oss.str();
}