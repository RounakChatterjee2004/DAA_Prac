#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

class DiningPhilosophers
{
private:
    vector<mutex> forks; // Mutex for each fork
    int numPhilosophers;
    bool terminate = false; // Flag to terminate threads

public:
    DiningPhilosophers(int numPhilosophers) : numPhilosophers(numPhilosophers), forks(numPhilosophers) {}

    // Philosopher's routine
    void philosopher(int id)
    {
        while (!terminate)
        {
            think(id);
            eat(id);
        }
    }

    // Simulate thinking
    void think(int id)
    {
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000 + 500)); // Random delay (500ms to 1500ms)
    }

    // Simulate eating
    void eat(int id)
    {
        int leftFork = id;                          // Left fork ID
        int rightFork = (id + 1) % numPhilosophers; // Right fork ID

        // Ensure philosophers always lock the lower-numbered fork first to avoid deadlock
        if (leftFork < rightFork)
        {
            lock_guard<mutex> leftLock(forks[leftFork]);
            lock_guard<mutex> rightLock(forks[rightFork]);
            cout << "Philosopher " << id << " is eating." << endl;
            this_thread::sleep_for(chrono::milliseconds(rand() % 1000 + 500)); // Random delay (500ms to 1500ms)
        }
        else
        {
            lock_guard<mutex> rightLock(forks[rightFork]);
            lock_guard<mutex> leftLock(forks[leftFork]);
            cout << "Philosopher " << id << " is eating." << endl;
            this_thread::sleep_for(chrono::milliseconds(rand() % 1000 + 500)); // Random delay (500ms to 1500ms)
        }
    }

    // Function to start philosopher threads
    void startPhilosophers()
    {
        vector<thread> threads;

        // Create threads for each philosopher
        for (int i = 0; i < numPhilosophers; i++)
        {
            threads.push_back(thread(&DiningPhilosophers::philosopher, this, i));
        }

        // Let the simulation run for 10 seconds
        this_thread::sleep_for(chrono::seconds(10));
        terminate = true; // Signal threads to terminate

        // Wait for all threads to finish
        for (auto &t : threads)
        {
            t.join();
        }
    }
};

int main()
{
    srand(time(0));          // Seed random number generator
    int numPhilosophers = 5; // Number of philosophers
    DiningPhilosophers dp(numPhilosophers);
    dp.startPhilosophers(); // Start the simulation
    return 0;
}
