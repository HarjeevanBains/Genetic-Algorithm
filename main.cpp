#include <iostream>
#include <random>
#include "tour.hpp"

double generateCoordinate() {
    static default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(0, 1000);
    return distribution(generator);
}

list<city> makeCityList(int size){
    char name = 'A';
    list<city> mix;
    for(int i =0; i<size;++i){
        mix.push_back({name++,generateCoordinate(),generateCoordinate()});
    }
    return mix;
}

void printCities(list<city> &cities) {
    list<city>::iterator cityIT;
    for (cityIT = cities.begin(); cityIT != cities.end(); ++cityIT) {
        cout << (*cityIT) << endl;
    }
}

using namespace std;
int main() {
    list<city> mix = makeCityList(10);
   // city a{name++,generateCoordinate(),generateCoordinate()};
    //city b{name++,generateCoordinate(),generateCoordinate()};
    cout << "City info:" << "\n"<< endl;
    printCities(mix);
    return 0;
}