#include <iostream>
#include <random>
#include <algorithm>
#include <cassert>
#include "tour.hpp"

constexpr int CITIES_IN_TOUR = 10;
constexpr int POPULATION_SIZE = 32;
constexpr int PARENT_POOL = 5;

using namespace std;

double generateCoordinate() {
    static default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(0, 1000);
    return distribution(generator);
}

int generateIndex() {
    static default_random_engine generator1(time(0));
    uniform_real_distribution<double> distribution(0, CITIES_IN_TOUR-1);
    return distribution(generator1);
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

tour randomTourFromList(list<tour> population){

}

list<city> combiner(tour tour1, tour tour2,int mixer) {
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

tour combineTwoTours(list<tour> allTours) {
    int mixer = generateIndex();
    //int counter = 0;
    tour parent1 = allTours.back();
    allTours.pop_back();
    tour parent2 = allTours.back();
    allTours.pop_back();

    list<city> cities1 = parent1.getLocations();
    list<city> cities2 = parent2.getLocations();
    list<city> newCities = combiner(cities1, cities2,mixer);

    tour newTour{newCities};
        cout<<"Mix Index: "<< mixer<<endl;
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

tour combineTwoTours1(list<tour> allTours) {
    int mixer = generateIndex();
    list<tour> parentPool1;
    list<tour> parentPool2;
    list<tour>::iterator tourIT1;
    list<tour>::iterator tourIT2;
    for (tourIT1 = parentPool1.begin(); tourIT1 != parentPool1.end(); ++tourIT1) {
        bool found = (std::find(parentPool1.begin(), parentPool1.end(), *tourIT1) != parentPool1.end());
    }
    while(parentPool1.size()<PARENT_POOL){
        for (tourIT1 = parentPool1.begin(); tourIT1 != parentPool1.end(); ++tourIT1) {
            bool found = (std::find(parentPool1.begin(), parentPool1.end(), *tourIT1) != parentPool1.end());
            if(!found){

            }
        }
    }
    tour parent1 = allTours.back();
    allTours.pop_back();
    tour parent2 = allTours.back();
    allTours.pop_back();

    list<city> newCities = combiner(parent1, parent2,mixer);

    tour newTour{newCities};
    return newTour;

}

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
    tour child = combineTwoTours(population);
    //allTours.push_back(newTour);
    //printTours(allTours);
    return 0;
}