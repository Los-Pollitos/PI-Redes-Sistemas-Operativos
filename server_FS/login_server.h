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
#define HASH_SIZE 32

#define PORT 8080

#include "file_system.h"
#include "log.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h> 
#include <unistd.h>
#include <vector>

class login_server {
  private:
    // Atributes
    FS* file_system;
    int connection;
    char data[DATA_SIZE];
    int message_count;
    struct sockaddr_storage ipRemoto;
    log* logger;
    bool continue_waiting;

    // Methods
    void find_data(std::string& username,  std::string& hash);
    void process_data(std::string ip_remote);
    void adapt_data(std::string& new_info);
    void find_create_info(std::string& username, std::string& hash);
    void append_the_user(std::string& username, std::string& hash);
    void load_from_file();
    void create_user();
    void delete_user();

    bool existing_user(std::string& username);
    void validate_data(std::string& username, std::string& hash);
    void give_token();
    void change_password();
    void change_token();

  public:
    login_server();
    ~login_server();
    void wait_for_request();
    void answer_request();
    void remove_the_user(std::string& username);

};

#endif // LOGIN_SERVER