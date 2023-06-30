/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef INTERMEDIARY_H
#define INTERMEDIARY_H

#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log.h"

#define DATA_SIZE 256
#define HASH_SIZE 30
#define PORT_C 9090
#define PORT_FS 8080
#define PORT_DB 1024


class intermediary {
  private:
    int connection;
    char data[DATA_SIZE];
    int message_count;
    bool continue_waiting;
    log * logger;
    struct sockaddr_storage ipRemoto;
    std::string send_and_receive_login(std::string ip_remote);
    void send_and_receive_data_base(std::string ip_remote);
    void manage_user_case(std::string ip_remote);
    void modify_network_case(std::string ip_remote);
    void set_up_intermediary(std::string ip_remote);
    void set_up_file_system(std::string ip_remote);
    void set_up_data_base(std::string ip_remote);

  public:
    intermediary();
    ~intermediary();
    void wait_for_request();
    void answer_request();
    void send_to_server(std::string ip_remote);
};

#endif
