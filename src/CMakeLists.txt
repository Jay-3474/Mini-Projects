add_executable(main main.cpp main.hpp)

install(TARGETS main DESTINATION bin)

find_package(
  Python3
  COMPONENTS Interpreter
  REQUIRED)

# Python file in same directory as CMakeLists.txt
set(PY_SRC "${CMAKE_SOURCE_DIR}/src/thread_example.py")
set(PY_DST "${CMAKE_BINARY_DIR}/thread_example.py")

# Sanity check
if(NOT EXISTS "${PY_SRC}")
  message(FATAL_ERROR "Could not find thread_example.py at: ${PY_SRC}")
endif()

# Step 1: Copy script into build directory
add_custom_command(
  OUTPUT "${PY_DST}"
  COMMAND ${CMAKE_COMMAND} -E copy "${PY_SRC}" "${PY_DST}"
  DEPENDS "${PY_SRC}"
  COMMENT "Copying thread_example.py to build directory")

# Step 2: Build target
add_custom_target(
  build_thread_example ALL
  DEPENDS "${PY_DST}"
  COMMENT "building thread_example.py")

# Step 3: Run target
add_custom_target(
  run_thread_example
  COMMAND ${Python3_EXECUTABLE} "${PY_DST}"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  DEPENDS build_thread_example
  COMMENT "Running thread_example.py")
