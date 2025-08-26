find_package(LibArchive REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/valid-update-container-UC_SIGNED.tar
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# set(CMAKE_EXE_LINKER_FLAGS "-larchive")

add_executable(untar untar.cpp)

# target_link_libraries(untar ${CMAKE_EXE_LINKER_FLAGS})

target_link_libraries(untar LibArchive::LibArchive)
