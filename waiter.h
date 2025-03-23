//
// Created by wojte on 21.03.2025.
//

#ifndef WAITER_H
#define WAITER_H

#include "philosopher.h"
#include <mutex>
#include <vector>

class philosopher;

class waiter {
    void sort_philosophers();

public:
    std::vector<philosopher *> philosophers;
    std::mutex waiterMutex;
    waiter();

    bool Decide(int id);
    void add_philosopher(philosopher *philosopher);
};


#endif //WAITER_H
