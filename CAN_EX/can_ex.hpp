#ifndef can_ex_H_
#define can_ex_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <cmath>

using namespace std;

class CAN_EX
{
private:
  unsigned int _SOF : 1;
  unsigned int _Identifier : 11;
  unsigned int _SRR : 1;
  unsigned int _IDE : 1;
  unsigned int _Identifier_ex : 18;
  unsigned int _RTR : 1;
  unsigned int _R0 : 1;
  unsigned int _R1 : 1;
  unsigned int _DLC : 4;
  string _data;
  unsigned int _CRC : 15;
  unsigned int _CRC_Delimiter : 1;
  unsigned int _Ack : 1;
  unsigned int _Ack_Delimiter : 1;
  unsigned int _EOF : 7;

public:
  CAN_EX()
      : _SOF(0)
      , _SRR(1)
      , _IDE(1)
      , _RTR(0)
      , _R0(1)
      , _R1(1)
      , _CRC_Delimiter(1)
      , _Ack(1)
      , _Ack_Delimiter(1)
      , _EOF(127)
      , _Identifier(0)
      , _Identifier_ex(0)
      , _DLC(0)
      , _data(" ")
      , _CRC(0){};

  void mem_init(unsigned int ident, unsigned int ident_ex, unsigned int DLC, string data, unsigned int CRC)
  {
    _Identifier = ident;
    _Identifier_ex = ident_ex;
    _DLC = DLC;
    _data = data;
    _CRC = CRC;
  }

  void _print()
  {
    cout << "*****##################################################*****" << endl;
    cout << "_SOF : " << _SOF << endl;
    cout << "_Identifier : " << _Identifier << endl;
    cout << "_SRR : " << _SRR << endl;
    cout << "_IDE : " << _IDE << endl;
    cout << "_Identifier_ex : " << _Identifier_ex << endl;
    cout << "_RTR : " << _RTR << endl;
    cout << "_R0 : " << _R0 << endl;
    cout << "_R1 : " << _R1 << endl;
    cout << "_DLC : " << _DLC << endl;
    cout << "_data : " << _data << endl;
    cout << "_CRC : " << _CRC << endl;
    cout << "_CRC_Delimiter : " << _CRC_Delimiter << endl;
    cout << "_ACK : " << _Ack << endl;
    cout << "_ACK_Delimiter : " << _Ack_Delimiter << endl;
    cout << "_EOF : " << _EOF << endl;
    cout << "*****#################################################*****" << endl;
  }

  ~CAN_EX(){};
};

#endif  // can_ex_H_
