#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

#include "philosopher.h"
#include "waiter.h"


class Display {
    std::vector<philosopher*> philosophers;

public:
    Display(std::vector<philosopher*> philosophers) {
        this->philosophers = philosophers;
    }

    void Run() {
        while (true) {
        std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
        for (auto philosopher: philosophers) {
            if (philosopher->is_eating()) {
                std::cout << "Philosopher " << philosopher->get_id() << " is eating" << std::endl;
            }
            else {
                std::cout << "Philosopher " << philosopher->get_id() << " didint eat for " << philosopher->check_hunger() << std::endl;
            }
        }
        std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            //sleep for 1 second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main() {
    //those are the variables needed to start the simulation that will later be used to create the objects
    int sleepsec;
    int number_of_philosophers;
    //This part of code gets all the settings for simulation from users
    std::cout << "How many philosophers should feast ?" << std::endl
    << "number of philosophers = ";
    std::cin >> number_of_philosophers;
    std::cout << std::endl <<"There will be as many forks as there are filosophers" << std::endl;
    std::cout << "How many seconds should each philosopher eat?" << std::endl;
    std::cout << "sleepsec = ";
    std::cin >> sleepsec;
    std::cout << "Each philosopher will eat for " << sleepsec << " seconds." << std::endl;


    //creating the objects
    std::vector<philosopher*> philosophers;
    std::mutex forks[number_of_philosophers];
    waiter wtr = waiter();

    for (int i = 0; i < number_of_philosophers; i++) {
        philosophers.push_back(new philosopher(i, &wtr, &forks[i], &forks[(i + 1) % number_of_philosophers], sleepsec));
        wtr.add_philosopher(philosophers[i]);
    }

    std::cout << "Simulation started";

    //runnin each philosopher in a separate thread
    std::vector<std::thread> threads;
    for (auto philosopher: philosophers) {
        threads.push_back(std::thread(&philosopher::run, philosopher));
    }
    //creating the display object
    Display display(philosophers);
    //running the display in a separate thread
    std::thread displayThread(&Display::Run, &display);
    //runnign while q is not pressed
    while (std::cin.get() != 'q') {
    }
}
