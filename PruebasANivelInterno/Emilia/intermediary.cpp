
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PORT_NUM 1500
#define CLIENT 0
#define LOGIN 1
#define DATA 2

int main() {
  char buffer[BUF_SIZE];

  struct sockaddr_in server_addr;

  // Establish conetion:
  int client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0) {
    std::cerr << "\nIntermediary: Error establishing socket..." << std::endl;
    return -1;
  }
  std::cout << "Intermediary: Server was initialized propperly" << std::endl;

  server_addr.sin_family = AF_INET;  // always set to this
  server_addr.sin_addr.s_addr = htons(INADDR_ANY); // IP of host as a port number
  server_addr.sin_port = htons(PORT_NUM);

  // Binding the socket to an address 
  if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)  {
    std::cerr << "Intermediary: Error binding connection, the socket has already been established..." << std::endl;
    return -1;
  }

  socklen_t size = sizeof(server_addr);
  std::cout << "Intermediary: Looking for clients..." << std::endl;
  listen(/*socket file descriptor*/client,
     /*number of conections that the server can handle (max is 5)*/ 1);

  // accept returns a new file descriptor once a new conection is made
  // if there are no conections, the server is blocked
  int clientCount = 1;
  int server = accept(client,(struct sockaddr *)&server_addr, &size);

  // first check if it is valid or not
  if (server < 0) {
    std::cerr << "Intermediray:Error on accepting connection..." << std::endl;
  }

  // while there is a conection
  bool isExit = false;
  while (server > 0) {
    // say hello
    strcpy(buffer, "Intermediary: Server connected...\n");
    send(server, buffer, BUF_SIZE, 0);
    std::cout << "Intermediary: Connected with the client #" << clientCount << ", you are good to go..." << std::endl;

    do {
      recv(server, buffer, BUF_SIZE, 0);
      std::cout << "Intermediary: Server received: " << buffer << " \n";
      if (*buffer == '#') {
          isExit = true;
      }
    } while (*buffer != '#');
    
    // inet_ntoa converts packet data to IP, which was taken from client
    close(client);
  }
  std::cout << "\n\n Intermediary: Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
  close(server);
  std::cout << "\nIntermediary: Goodbye..." << std::endl;
  return 0;
}