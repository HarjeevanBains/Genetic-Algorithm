#include <cmath>
#include "tour.hpp"

tour::tour(list<city> cities, double rating) {
    locations = cities;
    fitness = rating;
}

tour::tour(list<city> cities) {
    locations = cities;
    fitness = calculateFitness(locations);
}

long tour::calculateFitness(list<city> list1) {
    long score = 0.0;
    long distance;
    list<city>::iterator it1;
    list<city>::iterator it2;
    for (it1 = list1.begin(), it2 = ++list1.begin(); it2 != list1.end(); ++it1, ++it2) {
        distance = calculateDistance(*it1,*it2);
        score += distance;
    }
    return score;
}

const list<city> &tour::getLocations() const {
    return locations;
}

int tour::getFitness() const {
    return fitness;
}

long tour::calculateDistance(city city1, city city2) {
    //Distance =(x2−x1)2+(y2−y1)2
    long distance;
    long part1 = fabs(pow((city2.getX() - city1.getX()), 2));
    long part2 = fabs(pow((city2.getY() - city1.getY()), 2));
    distance = fabs((sqrt(part1 + part2)));
    return distance;
}

bool operator<(const tour& lhs, const tour& rhs){
    return (lhs.getFitness() < rhs.getFitness());
}