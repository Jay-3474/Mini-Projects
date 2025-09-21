#ifndef PRINT_EX_HPP
#define PRINT_EX_HPP

#include <string>

class Printer {
public:
    Printer(const std::string& message);

    void printMessageRepeatedly(int durationInSeconds);

private:
    std::string message;
};

#endif // PRINT_EX_HPP
