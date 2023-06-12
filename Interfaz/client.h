#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <ctime>
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
    GET_CHANGE_TOKEN,  // 68
    CREATE_USER,  // 69
    DELETE_USER,  // 70
    PAYMENT_PROOF,  // 71
    WORK_PROOF,  // 72
    SALARY_PROOF,  // 73
    SALARY_CONSULT,  // 74
    RECORD_CONSULT,  // 75
    SEE_CONSULT_REQUESTS,  // 76
    CONSULT_REQUESTS,  // 77
    SEE_PROCESS_REQUESTS,  // 78
    PROCESS_REQUESTS,  // 79
    VACATION_REQUEST,  // 80
    CONSULT_VACATION,  // 81
    ANSWER_PAYMENT_PROOF,
    ANSWER_WORK_PROOF,
    ANSWER_SALARY_PROOF,
    USER_OFFICE,
    ALL_USERS_OFFICE,
    DATA_USER,
    GET_ROLES,
    CHANGE_PHONE,
    CHANGE_EMAIL,
    CHANGE_OFFICE_ID,
    CHANGE_ROLES,
    CHANGE_LABORAL_DATA,
    CHANGE_VACATIONS,
    ADD_RECORD,
    CHANGE_SHIFT
};

class client {
public:
    client();
    std::string send_and_receive(std::string to_send);
private:
    void adapt_data(char* data, std::string& new_info, int pos);
};

#endif // CLIENT_H
