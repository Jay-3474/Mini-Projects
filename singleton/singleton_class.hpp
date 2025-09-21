#ifndef SINGLETON_CLASS_HPP
#define SINGLETON_CLASS_HPP

#include <iostream>
#include <string>

class SingletonClass {
private:
    static SingletonClass* instance;

    // Private constructor to prevent instantiation
    SingletonClass() {}

public:
    static SingletonClass* getInstance();

    void print(const std::string& message);
};

#endif  // SINGLETON_CLASS_HPP
