//
// Created by wojte on 21.03.2025.
//

#include "waiter.h"
#include <mutex>
#include <vector>
#include "philosopher.h"
#include <algorithm>
#include <list>

void waiter::sort_philosophers() {
    std::sort(philosophers.begin(), philosophers.end(), [](philosopher *a, philosopher *b) {
        return a->check_hunger() < b->check_hunger();
    });
}

void waiter::add_philosopher(philosopher *philosopher) {
    philosophers.push_back(philosopher);
}

bool waiter::Decide(int id) {
    sort_philosophers();
    if (philosophers[0]->get_id() == id) {
        return false;
    }
    return true;
}

waiter::waiter() {

}


