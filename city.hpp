#pragma once

#include <iostream>

using namespace std;

class city {
private:
    double x, y;
    char name;
public:
    city(char name, double x, double y);

    double getX() const;
    double getY() const;
    const char &getName() const;

    friend ostream &operator<<(ostream &os, const city &m);
};

