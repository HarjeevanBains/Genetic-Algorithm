#pragma once

#include <iostream>
#include <list>
#include "city.hpp"

using namespace std;

class tour {
private:
    list<city> locations;
    int fitness;
public:
    const list<city> &getLocations() const;

    int getFitness() const;

    tour(list<city> locations, int fitness);

    tour(list<city> locations);

    long calculateFitness(list<city> list1);

    long calculateDistance(city city1, city city2);
};

