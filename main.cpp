#include <iostream>

#include "functions.hpp"


int main() {
    list<city> list1 = makeCityList(CITIES_IN_TOUR);
    list<list<city>> allList = createAllList(list1);
    list<tour> population = createAllTours(allList);
    population.sort();
    tour elite1 = findBestTour(population);
    list<tour> newPopulation;
    list<tour> newPopulation1;
    newPopulation.push_back(elite1);

    for (int i = 0; i < POPULATION_SIZE - 1; i++) {
        newPopulation.push_back(combineTwoTours1(population));
    }
    list<tour> finalPopulation = newPopulation;

    while (findBestTour(finalPopulation).getFitness() >= (elite1.getFitness() * IMPROVEMENT_FACTOR)) {
        for (int i = 0; i < POPULATION_SIZE - 1; i++) {
            newPopulation1.push_back(combineTwoTours1(newPopulation));
        }
        finalPopulation = newPopulation1;
        newPopulation1.clear();
    }
    finalPopulation.push_back(elite1);
    finalPopulation.sort();
    tour elite2 = findBestTour(finalPopulation);
        cout << "Original Elite Tour:" << endl;
        cout << elite1 << endl;
        printCities(elite1.getLocations());
        cout << "---" << endl;
        cout << "New Elite Tour:" << endl;
        cout << elite2 << endl;
        printCities(elite2.getLocations());
    //printTours(finalPopulation);
    //tour child = combineTwoTours1(population);

    return 0;
}