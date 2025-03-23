//
// Created by wojte on 21.03.2025.
//

#include "philosopher.h"

void philosopher::eat() {
    //check if the forks are availible in case there is a mistake from waiter
    if (!has_left_fork)
        if (!left_fork->try_lock())
            return;

    has_left_fork = true;

    if (!right_fork->try_lock()) {
        return;
    }

    //set eating to true and sleep for eatsec seconds
    eating = true;
    std::this_thread::sleep_for(std::chrono::seconds(eatsec));
    //when done eating set eating to false and unlock the forks
    eating = false;
    //update the last eaten time
    last_eaten = time(NULL);
    has_left_fork = false;
    left_fork->unlock();
    right_fork->unlock();
}


void philosopher::try_eating() {
    if (!wtr->waiterMutex.try_lock()) {
        return;
    }
    if (wtr->Decide(id)) {
        wtr->waiterMutex.unlock();
        eat();
        return;
    }
    wtr->waiterMutex.unlock();
    return;
}

void philosopher::run() {
    while (true) {
        try_eating();
    };
}

bool philosopher::is_eating() {
    return eating;
}

int philosopher::check_hunger() {
    int count = time(NULL) - last_eaten;
    return count;
}

int philosopher::get_id() {
    return id;
}

philosopher::philosopher(int id, class waiter *waiter, std::mutex *left_fork, std::mutex *right_fork, int eatsec) {
    this->id = id;
    this->wtr = waiter;
    this->left_fork = left_fork;
    this->right_fork = right_fork;
    this->eatsec = eatsec;
    eating = false;
    last_eaten = time(NULL);
    has_left_fork= false;
}
