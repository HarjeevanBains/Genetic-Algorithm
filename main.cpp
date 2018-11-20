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

void printCities(list<city> &cities) {
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

long calculateDistance(city city1, city city2) {
    //Distance =(x2−x1)2+(y2−y1)2
    long distance = 0.0;
    long part1 = abs(pow((city2.getX() - city1.getX()), 2));
    long part2 = abs(pow((city2.getY() - city1.getY()), 2));
    distance = abs((sqrt(part1 + part2)));
    return distance;
}

long calculateScore(list<city> list1) {
    long score = 0.0;
    //Distance =(x2−x1)2+(y2−y1)2
    long distance = 0.0;
    list<city>::iterator it1;
    list<city>::iterator it2;
    for (it1 = list1.begin(), it2 = ++list1.begin(); it2 != list1.end(); ++it1, ++it2) {
        distance = calculateDistance(*it1,*it2);
        score += distance;
    }
    return score;
}


int main() {
    list<city> list1 = makeCityList(10);
    city a{'A',0,0};
    city b{'B',5,5};
    cout << "City info:" << "\n" << endl;
   // printCities(list1);
    cout << "Distance of list1: " << calculateScore(list1) << endl;
    cout << "----" << endl;
    list<city> mix1 = mixCities(list1);
    //printCities(mix1);
    cout << "Distance of mix1: " << calculateScore(mix1)<<endl;
    cout << "----" << endl;
    list<city> mix2 = mixCities(list1);
    //printCities(mix2);
    cout << "Distance of mix2: " << calculateScore(mix2)<<endl;
    cout << "----" << endl;
    cout << "Distance between city1 and city2: " << calculateDistance(a,b);
    return 0;
}