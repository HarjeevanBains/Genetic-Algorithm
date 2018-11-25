#pragma once

#include <random>
#include <algorithm>
#include <vector>
#include "tour.hpp"


constexpr int CITIES_IN_TOUR = 10;
constexpr int POPULATION_SIZE = 32;
constexpr int PARENT_POOL_SIZE = 5;
constexpr int NUMBER_OF_PARENTS = 2;
constexpr double IMPROVEMENT_FACTOR = .7;
constexpr int MUTATION_RATE = 5;//Whole number as percent

using namespace std;

double generateCoordinate() {
    static default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(0, 1000);
    return distribution(generator);
}

int generateIndex(int min, int max) {
    static default_random_engine generator1(time(0));
    uniform_real_distribution<double> distribution(min, max);
    return distribution(generator1);
}

vector<unsigned int> generateMixPoints() {
    vector<unsigned int> points;
    points.push_back(generateIndex(1, CITIES_IN_TOUR - 1));
    for (int i = 1; i < NUMBER_OF_PARENTS - 1; i++) {
        points.push_back(generateIndex(points[i - 1] + 1, CITIES_IN_TOUR - 1));
    }
    return points;
}

list<city> makeCityList(int size) {
    int name = 1;
    list<city> mix;
    for (int i = 0; i < size; ++i) {
        string nameString = to_string(name);
        mix.push_back({nameString, generateCoordinate(), generateCoordinate()});
        name++;
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
        cout << "Distance of Tour " << i++ << " ";
        cout << (tourIT->getFitness()) << endl;
    }
}

list<city> mixCities(list<city> cities) {
    list<city> mixed;
    vector<city> copyVector{std::begin(cities), std::end(cities)};
    random_shuffle(copyVector.begin(), copyVector.end());
    copy(copyVector.begin(), copyVector.end(), std::back_inserter(mixed));
    return mixed;
}

list<list<city>> createAllList(list<city> list1) {
    list<list<city>> allList;
    srand(time(0));
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
    return best;
}

tour findSecondBestTour(list<tour> tours) {
    tours.sort();
    vector<tour> copyVector{std::begin(tours), std::end(tours)};
    tour best = copyVector[1];
    return best;
}

tour randomTourFromList(list<tour> population) {
    int n = generateIndex(0, population.size());
    list<tour>::iterator tourIT;
    int i = 0;
    tour result{population.back()};
    for (tourIT = population.begin(); i <= n; ++tourIT) {
        if (i == n) {
            result = *tourIT;
        }
        i++;
    }
    return result;
}


vector<list<city>> cityFromTour(vector<tour> bestTours) {
    vector<list<city>> citiesVector;
    for (unsigned int i = 0; i < bestTours.size(); i++) {
        citiesVector.push_back(bestTours[i].getLocations());
    }
    return citiesVector;
}

list<city> combiner1(vector<list<city>> bestTours, vector<unsigned int> mixers) {
    unsigned int counter = 0;
    unsigned int start = 0;
    unsigned int listSize = bestTours[0].size();
    list<city> newCities;

    vector<vector<city>> copyVector;

    for (int i = 0; copyVector.size() < bestTours.size(); i++) {
        vector<city> copyVectorInitial{std::begin(bestTours[i]), std::end(bestTours[i])};
        copyVector.push_back(copyVectorInitial);
    }


    while (counter < mixers.size()) {
        for (int i = start; start < mixers[counter]; ++i) {
            bool found = (std::find(newCities.begin(), newCities.end(), copyVector[counter][start]) != newCities.end());
            if (!found) {
                newCities.push_back(copyVector[counter][start]);
                //start++;
            }
            start++;
        }
        counter++;
    }

    while (newCities.size() < listSize) {
        for (int i = start; newCities.size() < listSize; i++) {
            bool found = (std::find(newCities.begin(), newCities.end(), copyVector[counter][start]) != newCities.end());
            if (!found) {
                newCities.push_back(copyVector[counter][start]);
            }
            if (start < listSize - 1) {
                start++;
            } else {
                start = 0;
            }
        }
    }
    return newCities;

}

vector<list<tour>> generateParentPools(list<tour> allTours) {
    int counter = 0;
    vector<list<tour>> myParents;
    list<tour> tourCounter;
    while (counter < NUMBER_OF_PARENTS) {
        while (tourCounter.size() < PARENT_POOL_SIZE) {
            tour randomTour = randomTourFromList(allTours);
            bool found = (std::find(tourCounter.begin(), tourCounter.end(), randomTour) !=
                          tourCounter.end());
            if (!found) {
                tourCounter.push_back(randomTour);
            }
        }
        counter++;
        myParents.push_back(tourCounter);
        tourCounter.clear();
    }
    return myParents;
}

void swapList(list<city> &input){
    int randomIndex = generateIndex(0, input.size()-2);
    vector<city> copyVector{std::begin(input), std::end(input)};
    city one = copyVector[randomIndex];
    city two = copyVector[randomIndex+1];
    copyVector[randomIndex] = two;
    copyVector[randomIndex+1] = one;
    copy(copyVector.begin(), copyVector.end(), std::back_inserter(input));
}

tour mutate(tour input) {
    list<city> inputTourCities = input.getLocations();
    int randomCheck = generateIndex(1, 100);
    vector<int> mutationSizePool;

    while (mutationSizePool.size() < MUTATION_RATE) {
        int random = generateIndex(1, 100);
        bool found = (std::find(mutationSizePool.begin(), mutationSizePool.end(), random) !=
                      mutationSizePool.end());
        if (!found) {
            mutationSizePool.push_back(random);
        }
    }

    bool contains = (std::find(mutationSizePool.begin(), mutationSizePool.end(), randomCheck) !=
                     mutationSizePool.end());
    if (contains) {
        swapList(inputTourCities);
        tour output{inputTourCities};
        return output;
    }

    return input;
}

tour combineTwoTours1(list<tour> allTours) {
    vector<unsigned int> mixer = generateMixPoints();
    vector<list<tour>> allParents = generateParentPools(allTours);
    vector<tour> bestToursFromParentsABC;
    for (int i = 0; i < NUMBER_OF_PARENTS; i++) {
        bool contain = (
                std::find(bestToursFromParentsABC.begin(), bestToursFromParentsABC.end(),
                          (findBestTour(allParents[i]))) !=
                bestToursFromParentsABC.end());
        if (!contain) {
            bestToursFromParentsABC.push_back(findBestTour(allParents[i]));
        } else {
            bestToursFromParentsABC.push_back(findSecondBestTour(allParents[i]));
        }
    }

    vector<list<city>> citiesList = cityFromTour(bestToursFromParentsABC);
    list<city> newCities = combiner1(citiesList, mixer);
    tour newTour{newCities};
/**
    cout << "I didn't crash!" << endl;

    cout << "INDEX'S : ";
    for (unsigned int k = 0; k < mixer.size(); k++) {
        cout << mixer[k] << ", ";
    }
    cout << " " << endl;
    cout << "---" << endl;
    for (unsigned int j = 0; j < citiesList.size(); j++) {
        cout << "PARENT: " << (j + 1) << endl;
        printCities(citiesList[j]);
        cout << "---" << endl;
    }
    cout << "Child: " << newTour.getFitness() << endl;
    printCities(newTour.getLocations());
    **/
    newTour = mutate(newTour);
    return newTour;

}

void run(){
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


    int counter = 0;

    while (findBestTour(finalPopulation).getFitness() >= (elite1.getFitness() * IMPROVEMENT_FACTOR)) {
        for (int i = 0; i < POPULATION_SIZE - 1; i++) {
            newPopulation1.push_back(combineTwoTours1(newPopulation));
        }
        finalPopulation = newPopulation1;
        newPopulation1.clear();
        counter++;
        if(counter % 100 == 0){
            cout<<"Program has run "<<counter<<" times with no result, consider changing the IMPROVEMENT_FACTOR"<<endl;
        }
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
}