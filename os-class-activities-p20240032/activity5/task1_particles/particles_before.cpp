// task1_before_semaphore.cpp
// use g++ particles_before.cpp -pthread -o before to compile


#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>

using namespace std;

const int BUFFER_CAPACITY = 100;

vector<string> buffer;

long long producedPairs = 0;
long long packagedPairs = 0;

bool stopSimulation = false;

bool verifyPair(const string& p1, const string& p2)
{
    size_t a1 = p1.find("-P");
    size_t a2 = p2.find("-P");

    if (a1 == string::npos || a2 == string::npos)
        return false;

    return p1.substr(0, a1) == p2.substr(0, a2);
}

void producer(int machineId)
{
    int pairId = 1;

    while (!stopSimulation)
    {
        string p1 = "M" + to_string(machineId) +
                    "-" + to_string(pairId) + "-P1";

        string p2 = "M" + to_string(machineId) +
                    "-" + to_string(pairId) + "-P2";

        if (buffer.size() >= BUFFER_CAPACITY)
        {
            cout << "The producing machine is broken" << endl;
            stopSimulation = true;
            return;
        }

        buffer.push_back(p1);

        this_thread::sleep_for(
            chrono::milliseconds(rand() % 5));

        buffer.push_back(p2);

        producedPairs++;

        pairId++;

        this_thread::sleep_for(
            chrono::milliseconds(rand() % 10));
    }
}

void consumer()
{
    while (!stopSimulation)
    {
        if (buffer.size() < 2)
        {
            cout << "The packaging machine is broken" << endl;
            stopSimulation = true;
            return;
        }

        string p1 = buffer.front();
        buffer.erase(buffer.begin());

        this_thread::sleep_for(
            chrono::milliseconds(rand() % 5));

        if (buffer.empty())
        {
            cout << "The packaging machine is broken" << endl;
            stopSimulation = true;
            return;
        }

        string p2 = buffer.front();
        buffer.erase(buffer.begin());

        if (!verifyPair(p1, p2))
        {
            cout << "Pairs are incorrect" << endl;
            cout << p1 << " + " << p2 << endl;

            stopSimulation = true;
            return;
        }

        packagedPairs++;

        cout << "Produced pairs: "
             << producedPairs
             << " | Packaged pairs: "
             << packagedPairs
             << " | Buffer particles: "
             << buffer.size()
             << endl;

        this_thread::sleep_for(
            chrono::milliseconds(rand() % 10));
    }
}

int main()
{
    srand(time(nullptr));

    thread p1(producer, 1);
    thread p2(producer, 2);
    thread p3(producer, 3);
    thread p4(producer, 4);

    thread c(consumer);

    p1.join();
    p2.join();
    p3.join();
    p4.join();
    c.join();

    return 0;
}