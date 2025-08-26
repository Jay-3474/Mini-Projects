find_program(GO_EXECUTABLE go REQUIRED)

# Output dir for binaries
set(BUILD_BIN_DIR "${CMAKE_BINARY_DIR}/bin")
file(MAKE_DIRECTORY "${BUILD_BIN_DIR}")

# Path to test.txt in build dir
set(TEST_FILE "${CMAKE_BINARY_DIR}/test.txt")
file(WRITE "${TEST_FILE}" "This is a test file that delete.go will delete.\n")

# Full paths to Go sources
set(HELLO_SRC "${CMAKE_SOURCE_DIR}/file_go/hello.go")
set(DELETE_SRC "${CMAKE_SOURCE_DIR}/file_go/delete.go")

# Make sure they exist before continuing
if(NOT EXISTS "${HELLO_SRC}")
  message(FATAL_ERROR "Missing file: ${HELLO_SRC}")
endif()
if(NOT EXISTS "${DELETE_SRC}")
  message(FATAL_ERROR "Missing file: ${DELETE_SRC}")
endif()

# Build hello.go
add_custom_command(
  OUTPUT "${BUILD_BIN_DIR}/hello"
  COMMAND ${GO_EXECUTABLE} build -o "${BUILD_BIN_DIR}/hello" "${HELLO_SRC}"
  DEPENDS "${HELLO_SRC}"
  COMMENT "Building hello.go")

add_custom_target(
  hello ALL
  DEPENDS "${BUILD_BIN_DIR}/hello"
  COMMENT "creating target hello")

# Build delete.go
add_custom_command(
  OUTPUT "${BUILD_BIN_DIR}/delete"
  COMMAND ${GO_EXECUTABLE} build -o "${BUILD_BIN_DIR}/delete" "${DELETE_SRC}"
  DEPENDS "${DELETE_SRC}"
  COMMENT "Building delete.go")

add_custom_target(
  delete ALL
  DEPENDS "${BUILD_BIN_DIR}/delete"
  COMMENT "creating target delete")

# Run delete.go (it will delete test.txt in build dir)
add_custom_target(
  run_delete
  COMMAND "${BUILD_BIN_DIR}/delete"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  DEPENDS delete
  COMMENT "Running delete.go to delete test.txt")

# Run hello.go
add_custom_target(
  run_hello
  COMMAND "${BUILD_BIN_DIR}/hello"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  DEPENDS hello
  COMMENT "Running hello.go")
