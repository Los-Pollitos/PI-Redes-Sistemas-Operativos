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

#include "data_base.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum request_types {
    CREATE_USER = 68,
    DELETE_USER,
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
    void find_data(std::string& username,  std::string& hash);
    void process_data();
    void see_process_requests();

public:
    data_server();
    ~data_server();
    void wait_for_request();
    void answer_request();
};

#endif // DATA_SERVER_H
