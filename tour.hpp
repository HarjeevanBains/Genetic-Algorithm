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
    tour(list<city> locations, int fitness);
};

