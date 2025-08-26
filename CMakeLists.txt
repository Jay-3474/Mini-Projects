cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)

set(PROJECT_NAME general)
project(${PROJECT_NAME} LANGUAGES CXX)
add_executable(${PROJECT_NAME} "")

include(CTest)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory(src)

add_subdirectory(calc)

add_subdirectory(meta-parser)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "--header-filter=src/*")
  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY
                                                   "${DO_CLANG_TIDY}")
else()
  message(STATUS "clang-tidy not found.")
endif()

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.[ch]pp)

  add_custom_target(
    TARGET
    format
    COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES}
    COMMENT "clang formater")
endif()
