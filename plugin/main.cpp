#include <iostream>
#include "subtractor/subtractor.hpp"
#include "my_first_projectConfig.h"
#ifdef USE_ADDER
    #include "adder/adder.hpp"
#endif

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello!...." << std::endl;

    std::cout << argv[0] << " version: " << my_first_project_VERSION_MAJOR << "." << my_first_project_VERSION_MINOR << std::endl;

#ifdef USE_ADDER
    std::cout << "with adder: " << add(30.5f, 50.7f) << std::endl;
#else
    std::cout << 30.5f + 50.7f << std::endl;
#endif

    std::cout << sub(50.7f, 30.5f) << std::endl;

    return 0;
}
