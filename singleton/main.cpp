#include "print_ex.hpp"
#include "singleton_class.hpp"

auto main() -> int
{

    Printer printer("Hello, world!");
    printer.printMessageRepeatedly(60);

    SingletonClass* instance1 = SingletonClass::getInstance();
    SingletonClass* instance2 = SingletonClass::getInstance();

    // Check if the instances are the same
    bool isSameInstance = (instance1 == instance2);
    std::cout << "Is the same instance? " << std::boolalpha << isSameInstance << std::endl;

    // Call the print method on the instance
    instance1->print("hello from singleton");


    return 0;
}