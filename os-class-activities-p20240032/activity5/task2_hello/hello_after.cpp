// compile before: g++ hello_after.cpp -o hello_after -pthread
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

int stage = 0; // keeps track of which letter to print

void process1() {
    std::unique_lock<std::mutex> lock(mtx);
    while (stage != 0) cv.wait(lock); // wait until it's time for H and E
    std::cout << "H" << "E";
    stage = 1; // signal process2 to print first L
    cv.notify_all();
}

void process2() {
    std::unique_lock<std::mutex> lock(mtx);
    while (stage != 1) cv.wait(lock); // wait for HE
    std::cout << "L";
    stage = 2; // signal second L
    cv.notify_all();

    while (stage != 2) cv.wait(lock);
    std::cout << "L";
    stage = 3; // signal process3
    cv.notify_all();
}

void process3() {
    std::unique_lock<std::mutex> lock(mtx);
    while (stage != 3) cv.wait(lock); // wait for both Ls
    std::cout << "O";
}

int main() {
    std::thread t1(process1);
    std::thread t2(process2);
    std::thread t3(process3);

    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;
    return 0;
}