#ifndef tcp_client_H_
#define tcp_client_H_

#include "can_ex.hpp"

using namespace std;

auto tcp_client(const char* server_ID, const char* port_num, CAN_EX* frame4) -> int;

#endif  // tcp_client_H_
