find_package(
  Python3
  COMPONENTS Interpreter
  REQUIRED)

# Root folder containing friend_numbers.py and features/
set(FRIENDS_CUCUMBER_DIR "${CMAKE_SOURCE_DIR}/friend_numbers_cucumber")

# Behave features folder
set(BEHAVE_TEST_DIR "${FRIENDS_CUCUMBER_DIR}/features")

# Tell Python to search in friends_number_cucumber
set(PYTHONPATH_VALUE "${FRIENDS_CUCUMBER_DIR}")

# Behave command
set(BEHAVE_CMD ${Python3_EXECUTABLE} -m behave ${BEHAVE_TEST_DIR})

# Target to run behave directly
add_custom_target(
  run_behave
  COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${BEHAVE_CMD}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running Behave tests with PYTHONPATH=${PYTHONPATH_VALUE}"
  VERBATIM)

# Add behave to CTest
enable_testing()
add_test(
  NAME behave
  COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${BEHAVE_CMD}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
