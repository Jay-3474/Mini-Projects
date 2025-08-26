find_package(LibArchive REQUIRED)

project(hello-world)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/executables")

add_executable(hello-world hello-world.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/VDC-example-update_container.zip
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# set(CMAKE_EXE_LINKER_FLAGS "-larchive")
add_executable(untar untar.cpp)
# target_link_libraries(untar ${CMAKE_EXE_LINKER_FLAGS})

target_link_libraries(untar LibArchive::LibArchive)

add_custom_target(
  create_tar_gz ALL
  COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "executables.tar.gz"
          "${EXECUTABLE_OUTPUT_PATH}"
  DEPENDS hello-world
  COMMENT "creating executables tar file")

add_custom_target(
  create_tar_bz2 ALL
  COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "executables.tar.bz2"
          "${EXECUTABLE_OUTPUT_PATH}"
  DEPENDS hello-world
  COMMENT "creating executables tar file")

add_custom_target(
  create_tar_xz ALL
  COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "executables.tar.xz"
          "${EXECUTABLE_OUTPUT_PATH}"
  DEPENDS hello-world
  COMMENT "creating executables tar file")

add_custom_target(
  create_tar ALL
  COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "executables.tar"
          "${EXECUTABLE_OUTPUT_PATH}"
  DEPENDS hello-world
  COMMENT "creating executables tar file")
