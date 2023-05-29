/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef LOGIN_SERVER
#define LOGIN_SERVER

#define DATA_SIZE 256
#define HASH_SIZE 30

#include "file_system.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class login_server {
  private:
    // Atributes
    FS *file_system;
    int connection;
    char data[DATA_SIZE];
    int message_count;
    struct sockaddr_storage ipRemoto;

    // Methods
    void load_from_file();
    void find_data(std::string& username,  std::string& password);

  public:
    login_server();
    ~login_server();
    void wait_for_request();
    void answer_request();
    void validate_data();
};

#endif // LOGIN_SERVER
