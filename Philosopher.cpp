//
// Created by wojte on 23.03.2025.
//


// Philosopher.cpp

#include "Philosopher.h"

Philosopher::Philosopher(int id, std::vector<std::mutex>& forks, std::mutex& cout_mutex, int eat_time, int think_time, std::priority_queue<std::pair<std::chrono::steady_clock::time_point, int>>& priority_queue, std::mutex& queue_mutex)
    : id(id), forks(forks), cout_mutex(cout_mutex), eat_time(eat_time), think_time(think_time), priority_queue(priority_queue), queue_mutex(queue_mutex) {

    if (id < (id + 1) % forks.size()) {
        left = id;
    } else {
        left = (id + 1) % forks.size();
    }

    if (left == id) {
        right = (id + 1) % forks.size();
    } else {
        right = id;
    }

    last_eat_time = std::chrono::steady_clock::now();
}

void safe_cout(std::mutex& m, std::string& str) {
    std::lock_guard<std::mutex> lock(m);
    std::cout << str;
}

void Philosopher::Run() {
    while (true) {
        think();
        pickForks();
        eat();
        releaseForks();
    }
}

void Philosopher::think() {
    std::string str = "Philosopher " + std::to_string(id) + " is thinking\n";
    safe_cout(cout_mutex, str);
    std::this_thread::sleep_for(std::chrono::seconds(think_time));
}

void Philosopher::pickForks() {
    std::lock_guard<std::mutex> lock(queue_mutex);
    priority_queue.push({std::chrono::steady_clock::now(), id});
    while (priority_queue.top().second != id) {
        std::this_thread::yield();
    }
    forks[left].lock();
    forks[right].lock();
    priority_queue.pop();
}

void Philosopher::eat() {
    std::string str = "Philosopher " + std::to_string(id) + " is eating after not eating for " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - last_eat_time).count()) + " seconds\n";
    last_eat_time = std::chrono::steady_clock::now();
    safe_cout(cout_mutex, str);
    std::this_thread::sleep_for(std::chrono::seconds(eat_time));
}

void Philosopher::releaseForks() {
    forks[right].unlock();
    forks[left].unlock();
    std::string str = "Philosopher " + std::to_string(id) + " has finished eating\n";
    safe_cout(cout_mutex, str);
}