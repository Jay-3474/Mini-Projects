cmake_minimum_required(VERSION 3.13.4)

project(my_first_project VERSION 1.0)

option(USE_ADDER "A simple library for adding 2 floats" ON)

if(USE_ADDER)

    add_subdirectory(adder)

    list(APPEND EXTRA_LIBS_DIRS adder)
    list(APPEND EXTRA_INCLUDES_DIRS "${PROJECT_SOURCE_DIR}/adder")
    list(APPEND EXTRA_LINK_LIBS adder)

endif()

configure_file(my_first_projectConfig.h.in my_first_projectConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

add_subdirectory(subtractor)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${EXTRA_INCLUDES_DIRS}
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE subtractor
    PUBLIC ${EXTRA_LIBS_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    ${EXTRA_LINK_LIBS}
    subtractor
)
