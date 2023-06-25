/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef DATA_SERVER_H
#define DATA_SERVER_H

#define DATA_SIZE 256
#define HASH_SIZE 30

#define PORT 1024


#include "data_base.h"
#include "log_generator.h"
#include "security.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <QDate>

class data_server {
private:
    // Atributes
    data_base * base;
    int connection;
    char data[DATA_SIZE];
    int message_count;
    bool continue_waiting;
    log_generator * logger;
    struct sockaddr_storage ipRemoto;
    std::string remote_ip;

    // Methods
    void adapt_data(char* data, std::string& new_info, int pos);
    void load_from_file();
    void load_offices();
    void load_employees();
    void load_laboral_data();
    void load_requests();
    void load_records();
    void consult_vacations();
    void find_data(std::string& username,  std::string& hash);
    void process_data();
    void see_process_requests();
    void find_next(std::string& line, int& pos);
    void copy_string(std::string& line, std::string& new_line, int from, int to);
    void give_role();
    void create_user_case();
    void delete_user_case();
    void get_user_office();
    void get_all_users_from_office();
    void get_data_user();
    void change_phone();
    void change_email();
    void change_vacations();
    void change_shift();
    void change_laboral_data();
    void change_office();
    void change_roles();
    void add_record();
    void consult_record();
    void consult_salary_case();
    void proof_case(std::string description);
    void obtain_create_information(std::string& username, std::string& identification, std::string& name, int& office);
    void see_consult_requests();
    void consult_request();
    void vacation_request();
    void process_requests();
    void decrypt_salary(std::string salary, std::string deductibles, int& salary_int, int& deductibles_int);
    void pdf_data_payment();
    void pdf_data_work();
    void pdf_data_salary();
    void fire_employee();
    void get_all_users();

public:
    data_server();
    ~data_server();
    void wait_for_request();
    void answer_request();
};

#endif // DATA_SERVER_H
