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
  CHANGE_TOKEN,  // 68
  CREATE_USER,  // 69
  DELETE_USER,   // 70
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
  CHANGE_JOB_TITLE,  // 95
  CHANGE_ROLES,  // 96
  CHANGE_LABORAL_DATA,  // 97
  CHANGE_VACATIONS  // 98
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
