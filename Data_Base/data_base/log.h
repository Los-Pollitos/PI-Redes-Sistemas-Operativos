/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef LOG
#define LOG


#include<string>
#include<fstream>

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
    USER_OFFICE,  // 87
    ALL_USERS_OFFICE,  // 88
    DATA_USER  // 89
};

class log {
private:
    std::string log_file_name;
    std::string server_name;
    std::string get_system_time();
    std::string get_request_type(char type);

public:
    log(std::string file_name, std::string server_name);
    void add_to_log(std::string ip, std::string send_or_receive ,std::string to_log);
    void add_answer_log(std::string ip, std::string send_or_receive ,std::string to_log);
};

#endif // LOG
