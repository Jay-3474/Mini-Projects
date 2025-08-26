# Specify where the Robot test file is located
set(ROBOT_TEST_FILE ${CMAKE_SOURCE_DIR}/calc/calc.robot)

# Specify where to place the Robot output (inside build dir)
set(ROBOT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/robot_results)

# Custom command to run Robot Framework and generate output
add_custom_command(
  OUTPUT ${ROBOT_OUTPUT_DIR}/output.xml
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ROBOT_OUTPUT_DIR}
  COMMAND robot --outputdir ${ROBOT_OUTPUT_DIR} ${ROBOT_TEST_FILE}
  DEPENDS ${ROBOT_TEST_FILE}
  COMMENT "Running Robot Framework test: calc.robot"
  VERBATIM)

# Create a custom target you can manually invoke
add_custom_target(
  run_robot_tests
  DEPENDS ${ROBOT_OUTPUT_DIR}/output.xml
  COMMENT "Running Robot Framework tests: output.xml")

# Optional: integrate with ctest so you can use `ctest`
enable_testing()

add_test(NAME RunRobotTest COMMAND robot --outputdir ${ROBOT_OUTPUT_DIR}
                                   ${ROBOT_TEST_FILE})
