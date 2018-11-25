#pragma once

#include <iostream>
#include <list>
#include "city.hpp"

using namespace std;

class tour {
private:
    list<city> locations;
    double fitness;
public:
    tour(list<city> locations);

    const list<city> &getLocations() const;

    int getFitness() const;

    tour(list<city> locations, double fitness);

    long calculateFitness(list<city> list1);

    long calculateDistance(city city1, city city2);

    friend bool operator<(const tour& lhs, const tour& rhs);
    friend bool operator==(const tour& lhs, const tour& rhs);
    friend bool operator!=(const tour& lhs, const tour& rhs);
    friend ostream &operator<<(ostream &os, const tour &m);

};

