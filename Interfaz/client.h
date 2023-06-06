#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define CLIENT_DATA_SIZE 256
#define PORT 9090


enum request_types {
    GET_LOGIN = 65,  // A
    GET_TOKEN, // B 66
    GET_CHANGE_PASSWORD, // C 67
    GET_CHANGE_TOKEN,
    CREATE_USER,
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
    ANSWER_VACATION_REQUEST,
    USER_OFFICE,
    ALL_USERS_OFFICE,
    DATA_USER
};

class client {
public:
    client();
    std::string send_and_receive(std::string to_send);
private:
    void adapt_data(char* data, std::string& new_info, int pos);
};

#endif // CLIENT_H
