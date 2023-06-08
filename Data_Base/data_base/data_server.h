/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef DATA_SERVER_H
#define DATA_SERVER_H

#define DATA_SIZE 256
#define HASH_SIZE 30

#define PORT 1024


#include "data_base.h"
#include "log_generator.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class data_server {
private:
    // Atributes
    data_base * base;
    int connection;
    char data[DATA_SIZE];
    int message_count;
    log_generator * logger;
    struct sockaddr_storage ipRemoto;

    // Methods
    void adapt_data(char* data, std::string& new_info, int pos);
    void load_from_file();
    void load_offices();
    void load_employees();
    void load_laboral_data();
    void load_requests();
    void load_records();
    void find_data(std::string& username,  std::string& hash);
    void process_data(std::string remote_ip);
    void see_process_requests();
    void find_next(std::string& line, int& pos);
    void copy_string(std::string& line, std::string& new_line, int from, int to);
    void give_role(std::string remote_ip);
    void create_user_case(std::string remote_ip);
    void delete_user_case(std::string remote_ip);

public:
    data_server();
    ~data_server();
    void wait_for_request();
    void answer_request();
};

#endif // DATA_SERVER_H
