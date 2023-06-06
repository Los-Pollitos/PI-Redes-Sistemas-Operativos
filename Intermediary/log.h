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
  GET_ROLES 
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
