//
// Created by wojte on 23.03.2025.
//

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <mutex>
#include <vector>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

class Philosopher {
public:
    Philosopher(int id, std::vector<std::mutex>& forks, std::mutex& cout_mutex, int eat_time, int think_time, std::priority_queue<std::pair<std::chrono::steady_clock::time_point, int>>& priority_queue, std::mutex& queue_mutex);
    void Run();

private:
    void think();
    void pickForks();
    void eat();
    void releaseForks();

private:
    int id, eat_time, think_time;
    std::vector<std::mutex>& forks;
    std::mutex& cout_mutex;
    std::priority_queue<std::pair<std::chrono::steady_clock::time_point, int>>& priority_queue;
    std::mutex& queue_mutex;
    int left, right;
    std::chrono::steady_clock::time_point last_eat_time;
};



#endif //PHILOSOPHER_H
