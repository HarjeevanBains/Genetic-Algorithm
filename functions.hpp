#pragma once

#include <random>
#include <algorithm>
#include <vector>
#include "tour.hpp"


constexpr int CITIES_IN_TOUR = 10;
constexpr int POPULATION_SIZE = 32;
constexpr int PARENT_POOL_SIZE = 5;
constexpr int NUMBER_OF_PARENTS = 2;

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

vector<int> generateMixPoints() {
    vector<int> points;
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

list<city> combiner(tour tour1, tour tour2, int mixer) {
    int counter = 0;
    list<city> cities1 = tour1.getLocations();
    list<city> cities2 = tour2.getLocations();
    list<city> newCities;
    list<city>::iterator cityIT1;
    list<city>::iterator cityIT2;
    for (cityIT1 = cities1.begin(); counter < mixer; ++cityIT1) {
        newCities.push_back(*cityIT1);
        counter++;
    }
    counter = 0;
    for (cityIT2 = cities2.begin(); cityIT2 != cities2.end(); ++cityIT2) {
        counter++;
        bool found = (std::find(newCities.begin(), newCities.end(), *cityIT2) != newCities.end());
        if ((counter > mixer) && !found) {
            newCities.push_back(*cityIT2);
        }
    }
    for (cityIT2 = cities2.begin(); cityIT2 != cities2.end(); ++cityIT2) {
        bool found = (std::find(newCities.begin(), newCities.end(), *cityIT2) != newCities.end());
        if (!found) {
            newCities.push_back(*cityIT2);
        }
    }
    return newCities;

}

vector<list<city>> cityFromTour(vector<tour> bestTours) {
    vector<list<city>> citiesVector;
    for (int i = 0; i < bestTours.size(); i++) {
        citiesVector.push_back(bestTours[i].getLocations());
    }
    return citiesVector;
}

list<city> combiner1(vector<list<city>> bestTours, vector<int> mixers) {
    int counter = 0;
    int start = 0;
    int listSize = bestTours[0].size();
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
            if (start < listSize-1) {
                start++;
            } else {
                start = 0;
            }
        }
    }
    return newCities;

}

/**
tour combineTwoTours(list<tour> allTours) {
    int mixer = generateIndex();
    //int counter = 0;
    tour parent1 = allTours.back();
    allTours.pop_back();
    tour parent2 = allTours.back();
    allTours.pop_back();

    list<city> cities1 = parent1.getLocations();
    list<city> cities2 = parent2.getLocations();
    list<city> newCities = combiner(cities1, cities2, mixer);

    tour newTour{newCities};
    cout << "Mix Index: " << mixer << endl;
    cout << "Parent1: " << parent1.getFitness() << endl;
    printCities(parent1.getLocations());
    cout << "---" << endl;
    cout << "Parent2: " << parent2.getFitness() << endl;
    printCities(parent2.getLocations());
    cout << "---" << endl;
    cout << "Child: " << newTour.getFitness() << endl;
    printCities(newTour.getLocations());
    return newTour;

}
**/
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

tour combineTwoTours1(list<tour> allTours) {
    vector<int> mixer = generateMixPoints();
    vector<list<tour>> allParents = generateParentPools(allTours);
    vector<tour> bestToursFromParentsABC;
    for (int i = 0; i < NUMBER_OF_PARENTS; i++) {
        bool contain = (
                std::find(bestToursFromParentsABC.begin(), bestToursFromParentsABC.end(), (findBestTour(allParents[i]))) !=
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

    cout << "I didn't crash!" << endl;

    cout << "INDEX'S : ";
    for (int k = 0; k < mixer.size(); k++) {
        cout << mixer[k] << ", ";
    }
    cout << " " << endl;
    cout << "---" << endl;
    for (int j = 0; j < citiesList.size(); j++) {
        cout << "PARENT: " << (j + 1) << endl;
        printCities(citiesList[j]);
        cout << "---" << endl;
    }
    cout << "Child: " << newTour.getFitness() << endl;
    printCities(newTour.getLocations());
    return newTour;

}