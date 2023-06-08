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
    CONSULT_USER_DATA,  // 82
    CHANGE_USER_DATA,  // 83
    ANSWER_PAYMENT_PROOF,  // 84
    ANSWER_WORK_PROOF,  // 85
    ANSWER_SALARY_PROOF,  // 86
    ANSWER_VACATION_REQUEST,  // 87
    USER_OFFICE,  // 88
    ALL_USERS_OFFICE,  // 89
    DATA_USER,  // 90
    GET_ROLES,  // 91
    CHANGE_PHONE,  // 92
    CHANGE_EMAIL,  // 93
    CHANGE_OFFICE_ID,  // 94
    CHANGE_ROLES,  // 95
    CHANGE_LABORAL_DATA,  // 96
    CHANGE_VACATIONS,  // 97
    FIRE_EMPLOYEE,  // 98
    ADD_RECORD  // 99
};

class client {
public:
    client();
    std::string send_and_receive(std::string to_send);
    std::string send_and_receive_cypher(std::string to_send);
private:
    void adapt_data(char* data, std::string& new_info, int pos);
};

#endif // CLIENT_H
