
/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */


#ifndef LOG_GENERATOR_H
#define LOG_GENERATOR_H

#include<string>

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

class log_generator
{
  public:
    log_generator();
    void set_params(std::string file_name, std::string server_name);
    void add_to_log(std::string ip, std::string send_or_receive ,std::string to_log);
    void add_answer_log(std::string ip, std::string send_or_receive ,std::string to_log);

  private:
    std::string log_file_name;
    std::string server_name;
    std::string get_system_time();
    std::string get_request_type(char type);
};

#endif // LOG_GENERATOR_H
