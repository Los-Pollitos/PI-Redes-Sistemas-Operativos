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

void log::add_to_log(std::string ip, std::string to_log) {
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

  log_file << get_system_time() << ":" << ip << ":" << to_log << "\n";

  log_file.close();
}
