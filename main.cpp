//CSC 326 Car Wash Team Project
//Alondra Camacho

//This program simulates a car wash running during a certain time frame while arrival time, waiting time, and time of completion is tracked. 
//The total number of customers and the average wait time is also calculated

#include <iostream>
#include "washing.cpp"

using namespace std;

// Function prototype
void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time);

// Main function
int main() {

    //declare variable to hold wash_time, arrival_prob, and total_time
    unsigned int wash_time, total_time;
    double arrival_prob;

    // User input - wash_time, arrival_prob, and total time
    cout << "Enter wash time in seconds: ";
    cin >> wash_time;
    cout << "Enter arrival probability (0 <= p <= 1): ";
    cin >> arrival_prob;
    cout << "Enter total simulation time in seconds: ";
    cin >> total_time;

    //call the car_wash_simulate() function
    car_wash_simulate(wash_time, arrival_prob, total_time);

    return 0;
}

// Simulation function
void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time) {
    // precondition - make sure arrival probabibity is between 0 and 1
    assert(arrival_prob >= 0);
    assert(arrival_prob <= 1);

    //create object to work with probability of customer arrival - with bool_source class
    bool_source arrival(arrival_prob);
    //create object to track average of waiting time - averager class
    averager wait_times;
    //create object to simulate the washer functions - washer class
    washer car_washer(wash_time);
    //declare a que to keep track of customers
    Que<unsigned int> car_queue;

    unsigned int current_time = 0;
    unsigned int cars_served = 0;

    //convert wash time to minutes and the total time to hours
        //60 seconds in a minute
        //3600 seconds in an hour
    double washTimeMinutes = wash_time / 60.0;
    double totalHours = total_time / 3600.0;

    //print the seconds and minutes it takes to wash the car
    //print arrival probability
    //and print the total time the car wash is open
    cout << "\nSimulation starts...\n";
    cout << "-------------------------------------------\n";
    cout << "Wash time per car: " << wash_time << " seconds (" << washTimeMinutes << " minutes)\n";
    cout << "Probability of car arrival per second: " << arrival_prob << "\n";
    cout << "Total simulation time: " << total_time << " seconds (" << totalHours << " hours).\n\n";
    cout << "-------------------------------------------\n";

    for (current_time = 0; current_time < total_time; ++current_time) {
        // Check for new car arrival
        if (arrival.query()) {

            //add arrival time to the customer queue
            car_queue.addQ(current_time);
        }

        //if the washer is not busy and not empty...
        if (!car_washer.is_busy() && !car_queue.empty()) {
            unsigned int arrival_time;

            //get customer, that's in front of queue, arrival time
            car_queue.removeQ(arrival_time);

            unsigned int wait_time = current_time - arrival_time + wash_time;
            wait_times.next_number(wait_time);

            //begin to wash the next car
            car_washer.start_washing();
            ++cars_served;

            // Print customer #, arrival time, wait time, and end time
            cout << "Car " << cars_served << ":\n";
            cout << "  Arrival Time: " << arrival_time << " seconds\n";
            cout << "  Wait Time: " << wait_time << " seconds\n";
            cout << "  Finish Time: " << (current_time + wash_time) << " seconds\n";
            cout << "-------------------------------------------\n";
        }
        
        //make a second pass in washer for the loop(each iteration represents a second)
        car_washer.one_second();
    }

    //display overall details...total customers and the average waiting time
    cout << "\nSimulation ends...\n";
    cout << "-------------------------------------------\n";
    cout << "Total Cars Served: " << cars_served << "\n";
    if (cars_served > 0) {
        cout << "Average Wait Time: " << wait_times.average() << " seconds\n";
    }
    else {
        cout << "No cars were served during this simulation.\n";
    }
}