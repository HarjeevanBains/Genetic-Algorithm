#include "city.hpp"

city::city(char place, double a, double b) {
    name = place;
    x = a;
    y = b;
}

const char &city::getName() const {
    return name;
}

double city::getX() const {
    return x;
}

double city::getY() const {
    return y;
}

ostream &operator<<(ostream &os, const city &m) {
    os << "CITY: " << m.name << endl;
    os << "X:" << m.x << endl;
    os << "Y:" << m.y << endl;
    os<<"\n";
    return os;
}
