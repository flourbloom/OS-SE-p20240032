//compile using: g++ hello_before.cpp -o hello_before -pthread
#include <iostream>
#include <thread>

void process1() {
    std::cout << "H";
    std::cout << "E";
}

void process2() {
    std::cout << "L";
}

void process3() {
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