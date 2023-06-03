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

/// Declare four of the rule-of-the-five methods
#define DECLARE_RULE4(Class, action) \
  Class(const Class& other) = action; \
  Class(Class&& other) = action; \
  Class& operator=(const Class& other) = action; \
  Class& operator=(Class&& other) = action
// Disable default methods for copying objects
#define DISABLE_COPY(Class) \
  DECLARE_RULE4(Class, delete)

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
  DISABLE_COPY(login_server);
  private:
    // Atributes
    FS *file_system;
    int connection;
    char data[DATA_SIZE];
    bool continue_waiting;
    int message_count;
    struct sockaddr_storage ipRemoto;

    // Methods
    void load_from_file();
    void find_data(std::string& username,  std::string& hash);
    void process_data();

  public:
    login_server();
    ~login_server();
    void wait_for_request();
    void answer_request();
    void start();
    void stop();
    void validate_data(std::string& username, std::string& hash);
    static login_server& get_instance() {
      static login_server server;
      return server;
    }
};

#endif // LOGIN_SERVER
