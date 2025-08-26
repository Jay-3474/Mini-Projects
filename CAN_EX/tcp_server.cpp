#include "tcp_server.hpp"
#include "crc_check.hpp"

// Server side
auto tcp_server(const char* port_num, CAN_EX* frame2) -> int
{
  // grab the port number
  int port = atoi(port_num);

  // setup a socket and connection tools
  sockaddr_in servAddr;
  bzero((char*)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(port);

  // open stream oriented socket with internet address
  // also keep track of the socket descriptor
  int serverSd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSd < 0)
  {
    cerr << "Error establishing the server socket" << endl;
    exit(0);
  }

  // bind the socket to its local address
  int bindStatus = bind(serverSd, (struct sockaddr*)&servAddr, sizeof(servAddr));
  if (bindStatus < 0)
  {
    cerr << "Error binding socket to local address" << endl;
    exit(0);
  }

  cout << "Waiting for a client to connect..." << endl;
  // listen for up to 5 requests at a time
  listen(serverSd, 5);

  // receive a request from client using accept
  // we need a new address to connect with the client
  sockaddr_in newSockAddr;
  socklen_t newSockAddrSize = sizeof(newSockAddr);

  // accept, create a new socket descriptor to
  // handle the new connection with client
  int newSd = accept(serverSd, (sockaddr*)&newSockAddr, &newSockAddrSize);
  if (newSd < 0)
  {
    cerr << "Error accepting request from client!" << endl;
    exit(1);
  }

  cout << "Connected with client!" << endl;

  // lets keep track of the session time
  struct timeval start1, end1;
  gettimeofday(&start1, NULL);
  // also keep track of the amount of data sent as well
  int bytesWritten = 0;

  std::string data;
  std::cout << "Enter the data to be transmitted: ";
  std::cin >> data;

  std::string generator;
  std::cout << "Enter the generator polynomial: ";
  std::cin >> generator;

  // If you really need getline afterwards:
  std::string extra;
  std::getline(std::cin >> std::ws, extra);

  int d;
  for (d = 0; data[d]; d++)
    ;

  frame2->mem_init(10, 20, d, data, 0);

  cout << "frame_2.....................##" << endl;
  frame2->_print();

  // send the message to client
  bytesWritten = send(newSd, (void*)&frame2, sizeof(data), 0);

  // we need to close the socket descriptors after we're all done
  gettimeofday(&end1, NULL);
  close(newSd);
  close(serverSd);

  cout << "********Session********" << endl;
  cout << "Bytes written by server: " << bytesWritten << endl;
  cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
  cout << "Connection closed..." << endl;

  return 0;
}
