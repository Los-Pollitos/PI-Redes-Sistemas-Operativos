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

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum request_types {
  CREATE_USER = 68, // D 68
  DELETE_USER, // E 69
  PAYMENT_PROOF, // 70
  WORK_PROOF,  // 71
  SALARY_PROOF,  // 72
  SALARY_CONSULT,  // 73
  RECORD_CONSULT,  // 74
  SEE_CONSULT_REQUESTS,  // 75
  CONSULT_REQUESTS,  // 76
  SEE_PROCESS_REQUESTS,  // 77
  PROCESS_REQUESTS,  // 78
  VACATION_REQUEST,  // 79
  CONSULT_VACATION,  // 80
  CONSULT_USER_DATA,  // 81
  CHANGE_USER_DATA,  // 82
  ANSWER_PAYMENT_PROOF,  // 83
  ANSWER_WORK_PROOF,  // 84
  ANSWER_SALARY_PROOF,  // 85
  ANSWER_VACATION_REQUEST,  // 86

  // las de modificar usuario
  USER_OFFICE,  // 87
  ALL_USERS_OFFICE,  // 88
  DATA_USER  // 89
};

class data_server {
private:
    // Atributes
    data_base * base;
    int connection;
    char data[DATA_SIZE];
    int message_count;
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
    void process_data();
    void see_process_requests();
    void find_next(std::string& line, int& pos);
    void copy_string(std::string& line, std::string& new_line, int from, int to);

public:
    data_server();
    ~data_server();
    void wait_for_request();
    void answer_request();
};

#endif // DATA_SERVER_H
