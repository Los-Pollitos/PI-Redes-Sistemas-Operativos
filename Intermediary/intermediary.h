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

// TODO(us): tener data base
// #include "data_base/data_base.h"

enum request_types {
  LOGIN = 0,
  TOKEN,
  CHANGE_PASSWORD,
  CREATE_USER,
  DELETE_USER,
  PAYMENT_PROOF,
  WORK_PROOF,
  SALARY_PROOF,
  SALARY_CONSULT,
  RECORD_CONSULT,
  CONSULT_REQUESTS,
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
  
  public:
    intermediary();
    ~intermediary();
    void wait_for_request();
    void answer_request();
    void send_to_server();
};

#endif
