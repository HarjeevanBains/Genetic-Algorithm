#pragma once

#include <iostream>

using namespace std;

class city {
private:
    double x, y;
    string name;
public:
    city(string name, double x, double y);

    double getX() const;
    double getY() const;
    const string &getName() const;

    friend ostream &operator<<(ostream &os, const city &m);
    friend bool operator==(const city& lhs, const city& rhs);
};

