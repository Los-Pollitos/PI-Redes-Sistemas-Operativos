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

#define DATA_SIZE 256
#define HASH_SIZE 30
#define PORT_C 9090
#define PORT_FS 8080
#define PORT_DB 1024

// TODO(us): tener data base
// #include "data_base/data_base.h"

enum request_types {
  LOGIN = 65,  // A
  TOKEN, // B 66
  CHANGE_PASSWORD, // C 67
  CREATE_USER, // D 68
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
  USER_OFFICE,
  ALL_USERS_OFFICE,
  DATA_USER
};

class intermediary {
  private:
    int connection;
    char data[DATA_SIZE];
    int message_count;
    struct sockaddr_storage ipRemoto;
    std::string send_and_receive_login();
    void send_and_receive_data_base();
  
  public:
    intermediary();
    ~intermediary();
    void wait_for_request();
    void answer_request();
    void send_to_server();
};

#endif
