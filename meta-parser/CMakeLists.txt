# find_package(json-c REQUIRED) find_package(jsoncpp REQUIRED)
# find_package(nlohmann_json REQUIRED)

add_executable(meta-parser meta-parser.cpp)
# target_link_libraries(meta-parser json-c::json-c jsoncpp::jsoncpp
# nlohmann_json::nlohmann_json)

# Copy the meta file after build
add_custom_command(
  TARGET meta-parser
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/meta-parser/vdc-update.meta
    ${CMAKE_BINARY_DIR}/meta-parser/vdc-update.meta
  COMMENT "Copying meta file to build folder")

install(TARGETS meta-parser DESTINATION bin)
