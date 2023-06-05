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

#define PORT 8080

#include "file_system.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum request_types {
  LOGIN = 65,
  TOKEN,
  CHANGE_PASSWORD,
  CREATE_USER,
  DELETE_USER,
};

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
    void find_data(std::string& username,  std::string& hash);
    void process_data();
    void adapt_data(std::string& new_info);
    void create_user(std::string& username,  std::string& hash);
    bool existing_user(std::string& username);

  public:
    login_server();
    ~login_server();
    void wait_for_request();
    void answer_request();
    void validate_data(std::string& username, std::string& hash);
    void give_token();
};

#endif // LOGIN_SERVER