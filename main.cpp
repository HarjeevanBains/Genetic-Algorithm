#include <iostream>

#include "functions.hpp"


int main() {
    list<city> list1 = makeCityList(CITIES_IN_TOUR);
    list<list<city>> allList = createAllList(list1);
    list<tour> population = createAllTours(allList);
    population.sort();
    printTours(population);
    tour elite1 = findBestTour(population);
    list<tour> newPopulation;
    newPopulation.push_back(elite1);
    for(int i = 0; i< POPULATION_SIZE -1 ;i++){
        newPopulation.push_back(combineTwoTours1(population));
    }
    cout<<"---"<<endl;
    newPopulation.sort();
    printTours(newPopulation);
    //tour child = combineTwoTours1(population);

    return 0;
}