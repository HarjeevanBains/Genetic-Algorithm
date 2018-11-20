#include <iostream>
#include <random>
#include <algorithm>
#include "tour.hpp"

using namespace std;

double generateCoordinate() {
    static default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(0, 1000);
    return distribution(generator);
}

list<city> makeCityList(int size) {
    char name = 'A';
    list<city> mix;
    for (int i = 0; i < size; ++i) {
        mix.push_back({name++, generateCoordinate(), generateCoordinate()});
    }
    return mix;
}

void printCities(list<city> cities) {
    list<city>::iterator cityIT;
    for (cityIT = cities.begin(); cityIT != cities.end(); ++cityIT) {
        cout << (*cityIT);
    }
}

list<city> mixCities(list<city> cities) {
    list<city> mixed;
    vector<city> copyVector{std::begin(cities), std::end(cities)};;
    random_shuffle(copyVector.begin(), copyVector.end());
    copy(copyVector.begin(), copyVector.end(), std::back_inserter(mixed));
    return mixed;
}

tour findBestTour(list<tour> tours){
    tour best = tours.front();
    list<tour>::iterator it1;
    for (it1 = tours.begin(); it1 != tours.end(); ++it1) {
        if(it1 ->getFitness() < best.getFitness()){
            best = *it1;
        }
    }
    return best;
}

int main() {
    list<city> list1 = makeCityList(10);
    tour tour1{list1};
    cout << "City info:" << "\n" << endl;
    //printCities(tour1.getLocations());
    cout << "Distance of list1: " << tour1.getFitness()<< endl;
    cout << "----" << endl;
    list<city> mix1 = mixCities(list1);
    tour tour2{mix1};
   // printCities(tour2.getLocations());
    cout << "Distance of mix1: " << tour2.getFitness()<<endl;
    cout << "----" << endl;
    list<city> mix2 = mixCities(list1);
    tour tour3{mix2};
    //printCities(tour3.getLocations());
    cout << "Distance of mix2: " << tour3.getFitness()<<endl;
    cout << "----" << endl;
    list<tour> tourList;
    tourList.push_back(tour1);
    tourList.push_back(tour2);
    tourList.push_back(tour3);
    tour bestTour = findBestTour(tourList);
    cout<<"Best Tour score: "<< bestTour.getFitness();

    return 0;
}