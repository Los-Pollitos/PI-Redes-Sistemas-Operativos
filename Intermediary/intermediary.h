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
#define PORT_C 1337
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
  PAYMENT_PROOF,
  WORK_PROOF,
  SALARY_PROOF,
  SALARY_CONSULT,
  RECORD_CONSULT,
  SEE_CONSULT_REQUESTS,
  CONSULT_REQUESTS,
  SEE_PROCESS_REQUESTS,
  PROCESS_REQUESTS,
  VACATION_REQUEST,
  CONSULT_VACATION,
  CONSULT_USER_DATA,
  CHANGE_USER_DATA,
  ANSWER_PAYMENT_PROOF,
  ANSWER_WORK_PROOF,
  ANSWER_SALARY_PROOF,
  ANSWER_VACATION_REQUEST
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
