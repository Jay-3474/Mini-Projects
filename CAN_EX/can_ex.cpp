#include "can_ex.hpp"
#include "tcp_client.hpp"
#include "tcp_server.hpp"
#include "crc_check.hpp"

void func_1(CAN_EX& frame1)
{

  cout << "frame_1.....................#" << endl;
  frame1._print();

  const char* port_num = "8080";

  int f1 = tcp_server(port_num, &frame1);

  cout << "function 1 result....." << f1 << endl;
}

void func_2(CAN_EX& frame3)
{

  cout << "frame_3.....................###" << endl;
  frame3._print();

  const char* port_num = "8080";
  const char* server_IP = "127.0.0.1";

  int f2 = tcp_client(server_IP, port_num, &frame3);

  cout << "function 2 result....." << f2 << endl;
}

int main(void)
{

  CAN_EX frame;
  cout << "size of an object : " << sizeof(frame) << endl;

  frame._print();

  thread t1(&func_1, std::ref(frame));
  thread t2(&func_2, std::ref(frame));
  t1.join();
  t2.join();

  return 0;
}
