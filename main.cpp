#include <iostream>

#include "functions.hpp"


int main() {
    list<city> list1 = makeCityList(CITIES_IN_TOUR);
    list<list<city>> allList = createAllList(list1);
    list<tour> population = createAllTours(allList);
    //printTours(allTours);
    tour bestTour = findBestTour(population);
    //cout << "Best Tour score: " << bestTour.getFitness() << endl;
    //cout << "Best tour order:" << endl;
    //printCities(bestTour.getLocations());
    //cout << "---" << endl;
    //tour newTour =
    tour child = combineTwoTours1(population);
    //allTours.push_back(newTour);
    //printTours(allTours);
    return 0;
}