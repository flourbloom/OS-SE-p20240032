// task1_after_semaphore.cpp
// use g++ particles_after.cpp -pthread -o after to compile

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

// Buffer settings
const int BUFFER_CAPACITY = 100;
const int PAIR_CAPACITY = 50;

// Shared buffer
vector<string> buffer;

// Custom semaphore class
class Semaphore {
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    Semaphore(int value) : count(value) {}

    void acquire() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]{ return count > 0; });
        count--;
    }

    void release() {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

// Semaphores
Semaphore emptyPairs(PAIR_CAPACITY);
Semaphore fullPairs(0);
Semaphore bufferMutex(1);

// Counters
atomic<long long> producedPairs(0);
atomic<long long> packagedPairs(0);
atomic<bool> stopSimulation(false);

// Verify that two particles belong to the same pair
bool verifyPair(const string& p1, const string& p2) {
    size_t a1 = p1.find("-P");
    size_t a2 = p2.find("-P");

    if (a1 == string::npos || a2 == string::npos)
        return false;

    return p1.substr(0, a1) == p2.substr(0, a2);
}

// Producer thread
void producer(int machineId) {
    int pairId = 1;

    while (!stopSimulation) {
        string p1 = "M" + to_string(machineId) + "-" + to_string(pairId) + "-P1";
        string p2 = "M" + to_string(machineId) + "-" + to_string(pairId) + "-P2";

        // Wait for empty space
        emptyPairs.acquire();
        bufferMutex.acquire();

        // Safety check
        if (buffer.size() > BUFFER_CAPACITY - 2) {
            cout << "The producing machine is broken" << endl;
            stopSimulation = true;
            bufferMutex.release();
            return;
        }

        buffer.push_back(p1);
        buffer.push_back(p2);

        producedPairs++;

        bufferMutex.release();
        fullPairs.release(); // Signal one full pair

        pairId++;

        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

// Consumer thread
void consumer() {
    while (!stopSimulation) {
        fullPairs.acquire();
        bufferMutex.acquire();

        if (buffer.size() < 2) {
            cout << "The packaging machine is broken" << endl;
            stopSimulation = true;
            bufferMutex.release();
            return;
        }

        string p1 = buffer.front();
        buffer.erase(buffer.begin());

        string p2 = buffer.front();
        buffer.erase(buffer.begin());

        if (!verifyPair(p1, p2)) {
            cout << "Pairs are incorrect" << endl;
            stopSimulation = true;
            bufferMutex.release();
            return;
        }

        packagedPairs++;

        cout << "Produced pairs: " << producedPairs
             << " | Packaged pairs: " << packagedPairs
             << " | Buffer particles: " << buffer.size() << endl;

        bufferMutex.release();
        emptyPairs.release();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

// Main
int main() {
    vector<thread> producers;
    for (int i = 1; i <= 4; i++) {
        producers.emplace_back(producer, i);
    }

    thread consumerThread(consumer);

    // Let it run indefinitely; stop manually with Ctrl+C
    for (auto& t : producers) t.join();
    consumerThread.join();

    return 0;
}