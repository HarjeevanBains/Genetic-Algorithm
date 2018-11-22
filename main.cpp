#include <iostream>
#include <random>
#include <algorithm>
#include "tour.hpp"

constexpr int CITIES_IN_TOUR = 32;
constexpr int POPULATION_SIZE = 32;

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

void printTours(list<tour> tours) {
    list<tour>::iterator tourIT;
    int i = 1;
    for (tourIT = tours.begin(); tourIT != tours.end(); ++tourIT) {
        cout <<"Distance of Tour "<< i++ <<" ";
        cout << (tourIT->getFitness())<<endl;
    }
}

list<city> mixCities(list<city> cities) {
    list<city> mixed;
    vector<city> copyVector{std::begin(cities), std::end(cities)};;
    random_shuffle(copyVector.begin(), copyVector.end());
    copy(copyVector.begin(), copyVector.end(), std::back_inserter(mixed));
    return mixed;
}

list<list<city>> createAllList(list<city> list1) {
    list<list<city>> allList;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        allList.push_back(mixCities(list1));
    }
    return allList;
}

list<tour> createAllTours(list<list<city>> list1) {
    list<tour> allTours;
    list<list<city>>::iterator cityIT;
    for (cityIT = list1.begin(); cityIT != list1.end(); ++cityIT) {
        tour tour1{*cityIT};
        allTours.push_back(tour1);
    }
    return allTours;
}

tour findBestTour(list<tour> tours) {
    tours.sort();
    tour best = tours.front();
    /**list<tour>::iterator it1;
    for (it1 = tours.begin(); it1 != tours.end(); ++it1) {
        if(it1 ->getFitness() < best.getFitness()){
            best = *it1;
        }
    }**/
    return best;
}

int main() {
    list<city> list1 = makeCityList(CITIES_IN_TOUR);
    list<list<city>> allList = createAllList(list1);
    list<tour> allTours = createAllTours(allList);
    
    printTours(allTours);
    tour bestTour = findBestTour(allTours);
    cout << "Best Tour score: " << bestTour.getFitness();
    return 0;
}