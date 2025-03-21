#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class Restaurant {
    std::mutex* forks;

    Restaurant(int forksCount) {
        forks = new std::mutex[forksCount];
    }
};

class Waiter {
    std::queue<int> waitingQueue;
    Restaurant* restaurant;
    std::mutex* waiterMutex;
    Waiter(Restaurant* restaurant) {
        this->restaurant = restaurant;
        waiterMutex = new std::mutex();
    }
    bool Decide(int id) {
    }
};

class Philosopher {
    int id;
    Restaurant* restaurant;
    Waiter* waiter;
    bool eating;
    std::mutex *left_fork;
    std::mutex *right_fork;
    std::mutex hungryMutex;
    int hungryCount;
    int sleepsec;

    Philosopher(int id, Restaurant* restaurant, Waiter* waiter, std::mutex left_fork, std::mutex right_fork,int sleepsec) {
        this->id = id;
        this->restaurant = restaurant;
        this->waiter = waiter;
        this->left_fork = &left_fork;
        this->right_fork = &right_fork;
        this->sleepsec = sleepsec;
        eating = false;
    }

    void Eat() {
        if (!left_fork->try_lock()) {
            std::cout <<"Philosopher " << id << "Tried to eat without left fork availible" << std::endl;
            return;
        }
        if (!right_fork->try_lock()) {
            std::cout <<"Philosopher " << id << "Tried to eat without right fork availible" << std::endl;
            left_fork->unlock();
            return;
        }
        eating = true;
        std::this_thread::sleep_for(std::chrono::seconds(sleepsec));
        hungryMutex.lock();
        hungryCount = 0;
        hungryMutex.unlock();
        eating = false;
        left_fork->unlock();
        right_fork->unlock();
    }

    void think() {
        std::this_thread::sleep_for(std::chrono::seconds(sleepsec/10));
        hungryMutex.lock();
        hungryCount++;
        hungryMutex.unlock();
    }

    int check_hunger() {
        hungryMutex.lock();
        int count = hungryCount;
        hungryMutex.unlock();
        return count;
    }

    void try_eating() {

    }

    void Run() {
        try_eating();
        think();
    }
};

int main() {

}
