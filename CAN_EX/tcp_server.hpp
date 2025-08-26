#ifndef tcp_server_H_
#define tcp_server_H_

#include "can_ex.hpp"

using namespace std;

auto tcp_server(const char* port_num, CAN_EX* frame2) -> int;

#endif  // tcp_server_H_
