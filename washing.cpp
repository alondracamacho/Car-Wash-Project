//CSC 326 Car Wash Team Project
//Alondra Camacho & Marc Flores

//This program simulates a car wash running during a certain time frame while arrival time, waiting time, and time of completion is tracked. 
//The total number of customers and the average wait time is also calculated

#include "washing.h"
#include <cstdlib> // For rand()

// Implementation of bool_source
bool_source::bool_source(double p) {
    assert(p >= 0 && p <= 1); //precondition. probability is between 0 and 1
    probability = p;
}

bool bool_source::query() const {
    return (rand() <  probability * RAND_MAX);
}

// Implementation of averager
averager::averager() {
    count = 0;
    sum = 0;
}

void averager::next_number(double value) {
    ++count;
    sum += value;
}

double averager::average() const {
    assert(count > 0);
    return sum / count;
}

// Implementation of washer
washer::washer(unsigned int s) {
    seconds_for_wash = s;
    wash_time_left = 0;
}

void washer::one_second() {
    if (is_busy()) {
        --wash_time_left;
}
}

void washer::start_washing() {
    assert(!is_busy());
    wash_time_left = seconds_for_wash;
}

