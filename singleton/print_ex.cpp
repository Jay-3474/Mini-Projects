#include "print_ex.hpp"
#include <iostream>

#include <chrono>
#include <thread>

Printer::Printer(const std::string& message) : message(message) {
    std::cout << message << std::endl;
}

void Printer::printMessageRepeatedly(int durationInSeconds) {
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(durationInSeconds);
    
    while (std::chrono::steady_clock::now() < endTime) {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}