
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PORT_NUM 1500 // NOTE that the port number is same for both client and server
#define TO_LOGIN 0
#define TO_DATA 1

#define IS_LOGIN 0
#define CHANGE_PASS 1
#define SEE_VACATIONS 2
#define ASK_VACATIONS 3
#define SEE_RECORD 4


int main() {
  char buffer[BUF_SIZE];
  char* ip = (char*)"127.0.0.";
  struct sockaddr_in server_addr;
  int client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0) {
    std::cout << "\nCli:Error establishing socket..." << std::endl;
    return -1;
  }
  std::cout << "Client has been propperly created" << std::endl;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT_NUM);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT_NUM);

  // this function returns returns 1 if the IP is valid
  // and 0 if invalid
  // inet_pton converts IP to packets
  // inet_ntoa converts back packets to IP
  //inet_pton(AF_INET, ip, &server_addr.sin_addr);

  /* ---------- CONNECTING THE SOCKET ---------- */
  /* ---------------- connect() ---------------- */

  if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
    std::cout << "Cli: Connection to the server port number: " << PORT_NUM << std::endl;
  }

  std::cout<< "Cli:Waiting for connection" << std::endl;
  recv(client, buffer, BUF_SIZE, 0);
  std::cout << "Cli: Connection confirmed " << std::endl;

  strcpy(buffer, "0, cjimenez");
  send(client, buffer, BUF_SIZE, 0);

  strcpy(buffer, "#");
  send(client, buffer, BUF_SIZE, 0);
  sleep(1);

  std::cout << "\nCli:Connection terminated.\nGoodbye...\n";
  close(client);
  return 0;
}