
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
  CHANGE_TOKEN,
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
  DATA_USER,
  GET_ROLES,
  CHANGE_PHONE,
  CHANGE_EMAIL,
  CHANGE_OFFICE_ID,
  CHANGE_JOB_TITLE,
  CHANGE_ROLES,
  CHANGE_SALARY,
  CHANGE_DEDUCTIONS
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
