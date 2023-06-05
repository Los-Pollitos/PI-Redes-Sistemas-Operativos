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
    USER_OFFICE,  // 87
    ALL_USERS_OFFICE,  // 88
    DATA_USER  // 89
};

class client {
public:
    client();
    std::string send_and_receive(std::string to_send);
private:
    void adapt_data(char* data, std::string& new_info, int pos);
};

#endif // CLIENT_H
