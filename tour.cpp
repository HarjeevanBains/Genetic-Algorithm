#include "tour.hpp"

tour::tour(list<city> cities, int rating) {
    locations = cities;
    fitness = rating;

}