//
// Created by wojte on 21.03.2025.
//

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "philosopher.h"
#include "waiter.h"
#include <thread>
#include <iostream>
#include <mutex>

class waiter;

class philosopher {
    bool has_left_fork;
    int id;
    waiter *wtr;
    bool eating;
    std::mutex *left_fork;
    std::mutex *right_fork;
    std::mutex hungryMutex;
    time_t last_eaten;
    int eatsec;

private:
    void eat();
    void try_eating();

public:
    void run();

    bool is_eating();

    int check_hunger();

    int get_id();

    philosopher(int id, waiter *waiter, std::mutex *left_fork, std::mutex *right_fork, int eatsec);
};


#endif //PHILOSOPHER_H
