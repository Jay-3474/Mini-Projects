#include "tcp_client.hpp"

// Client side
auto tcp_client(const char* server_ID, const char* port_num, CAN_EX* frame4) -> int
{
  // grab the IP address and port number
  const char* serverIp = server_ID;
  int port = atoi(port_num);

  // setup a socket and connection tools
  struct hostent* host = gethostbyname(serverIp);
  sockaddr_in sendSockAddr;
  bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
  sendSockAddr.sin_family = AF_INET;
  sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
  sendSockAddr.sin_port = htons(port);
  int clientSd = socket(AF_INET, SOCK_STREAM, 0);

  cout << "client ID............................... " << clientSd << endl;

  // try to connect...
  int status = connect(clientSd, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr));
  if (status < 0)
  {
    cout << "Error connecting to socket!" << endl;
    return 0;
  }

  cout << "Connected to the server!" << endl;

  int bytesRead = 0;
  struct timeval start1, end1;
  gettimeofday(&start1, NULL);

  memset(&frame4, 0, sizeof(frame4));

  bytesRead = recv(clientSd, (void*)&frame4, sizeof(frame4), 0);

  frame4->_print();

  gettimeofday(&end1, NULL);
  close(clientSd);

  cout << "********Session********" << endl;
  cout << "Bytes read by client: " << bytesRead << endl;
  cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
  cout << "Connection closed" << endl;

  return 0;
}
