#include "Philosopher.h"
#include <vector>
#include <thread>

int main() {
    std::cout << "How many philosophers should dine? \n";
    int num_philosophers ;
    std::cin >> num_philosophers;
    std::cout << "How long should the philosophers eat? \n";
    int eat_time;
    std::cin >> eat_time;
    std::cout << "How long should the philosophers think? \n";
    int think_time;
    std::cin >> think_time;


    std::mutex cout_mutex, queue_mutex;
    std::vector<std::mutex> forks(num_philosophers);
    std::priority_queue<std::pair<std::chrono::steady_clock::time_point, int>> priority_queue;


    std::vector<Philosopher> philosophers;
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers.push_back(Philosopher(i, forks, cout_mutex, eat_time, think_time,priority_queue, queue_mutex));
    }

    std::vector<std::thread> threads;
    for (auto& p : philosophers) {
        threads.emplace_back(&Philosopher::Run, &p);
    }

    for (auto& t : threads) {
        t.join();
    }
    return 0;
}