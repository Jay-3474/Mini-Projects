add_compile_options(-pthread)
add_compile_options(-g)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(can_ex can_ex.cpp tcp_client.cpp tcp_server.cpp crc_check.cpp)

install(TARGETS can_ex DESTINATION bin)
