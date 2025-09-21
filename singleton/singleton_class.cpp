#include "singleton_class.hpp"

SingletonClass* SingletonClass::getInstance() {
    static SingletonClass instance;
    return &instance;
}

void SingletonClass::print(const std::string& message) {
    std::cout << "Printing from SingletonClass: " << message << std::endl;
}
