/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */


#include "log.h"
#include <ctime>

log::log(std::string file_name, std::string server_name) {
  this->log_file_name = file_name;
  this->server_name = server_name;
}

std::string log::get_system_time() {
  time_t local_time = time(0);
  std::string to_return = ctime(&local_time);
  to_return = to_return.substr(0,to_return.size()-1);
  return to_return;
}

std::string log::get_request_type(char type) {
  std::string result = "";
  switch (type) {
    case LOGIN:
      result = "LOGIN";
      break;
    case TOKEN:
      result = "TOKEN";
      break;
    case CHANGE_PASSWORD:
      result = "CHANGE_PASSWORD";
      break;
    case CREATE_USER:
      result = "CREATE_USER";
      break;
    case DELETE_USER:
      result = "DELETE_USER";
      break;
    case PAYMENT_PROOF:
      result = "PAYMENT_PROOF";
      break;
    case WORK_PROOF:
      result = "WORK_PROOF";
      break;
    case SALARY_PROOF:
      result = "SALARY_PROOF";
      break;
    case SALARY_CONSULT:
      result = "SALARY_CONSULT";
      break;
    case RECORD_CONSULT:
      result = "RECORD_CONSULT";
      break;
    case SEE_CONSULT_REQUESTS:
      result = "SEE_CONSULT_REQUESTS";
      break;
    case CONSULT_REQUESTS:
      result = "CONSULT_REQUESTS";
      break;
    case SEE_PROCESS_REQUESTS:
      result = "SEE_PROCESS_REQUESTS";
      break;
    case PROCESS_REQUESTS:
      result = "PROCESS_REQUESTS";
      break;
    case VACATION_REQUEST:
      result = "VACATION_REQUEST";
      break;
    case CONSULT_VACATION:
      result = "CONSULT_VACATION";
      break;
    case CONSULT_USER_DATA:
      result = "CONSULT_USER_DATA";
      break;
    case CHANGE_USER_DATA:
      result = "CHANGE_USER_DATA";
      break;
    case ANSWER_PAYMENT_PROOF:
      result = "ANSWER_PAYMENT_PROOF";
      break;
    case ANSWER_WORK_PROOF:
      result = "ANSWER_WORK_PROOF";
      break;
    case ANSWER_SALARY_PROOF:
      result = "ANSWER_SALARY_PROOF";
      break;
    case ANSWER_VACATION_REQUEST:
      result = "ANSWER_VACATION_REQUEST";
      break;
    case USER_OFFICE:
      result = "USER_OFFICE";
      break;
    case ALL_USERS_OFFICE:
      result = "ALL_USERS_OFFICE";
      break;
    case DATA_USER:
      result = "DATA_USER";
      break;
  }

  return result;
}

void log::add_to_log(std::string ip, std::string send_or_receive, std::string to_log) {
  // try to open the log file to see if it exists
  std::ifstream check_file(this->log_file_name);
  if (!check_file.is_open()) {
    // if it does not exist, create it
    std::ofstream create_file(this->log_file_name);
    create_file << "Log file of " << server_name << "\n";
    create_file.close();
  } else {
    // File did exist, so close the file to avoid
    // leaving it open
    check_file.close();
  }
  // Open the file to be able to append to it
  std::fstream log_file;
  log_file.open(this->log_file_name, std::fstream::app| std::fstream::out);

  log_file << get_system_time() << ":" << ip << ":" << send_or_receive  << ":"
   << this->get_request_type(to_log[0]) << ":"<< to_log.substr(1) << "\n";

  log_file.close();
}
