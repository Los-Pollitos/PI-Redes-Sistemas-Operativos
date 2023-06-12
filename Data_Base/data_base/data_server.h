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

    // Methods
    void adapt_data(char* data, std::string& new_info, int pos);
    void load_from_file();
    void load_offices();
    void load_employees();
    void load_laboral_data();
    void load_requests();
    void load_records();
    void consult_vacations(std::string remote_ip);
    void find_data(std::string& username,  std::string& hash);
    void process_data(std::string remote_ip);
    void see_process_requests(std::string remote_ip);
    void find_next(std::string& line, int& pos);
    void copy_string(std::string& line, std::string& new_line, int from, int to);
    void give_role(std::string remote_ip);
    void create_user_case(std::string remote_ip);
    void delete_user_case(std::string remote_ip);
    void get_user_office(std::string remote_ip);
    void get_all_users_from_office(std::string remote_ip);
    void get_data_user(std::string remote_ip);
    void change_phone(std::string remote_ip);
    void change_email(std::string remote_ip);
    void change_vacations(std::string remote_ip);
    void change_shift(std::string remote_ip);
    void change_laboral_data(std::string remote_ip);
    void change_office(std::string remote_ip);
    void change_roles(std::string remote_ip);
    void add_record(std::string remote_ip);
    void consult_record(std::string remote_ip);
    void consult_salary_case(std::string remote_ip);
    void proof_case(std::string remote_ip, std::string description);
    void obtain_create_information(std::string& username, std::string& identification, std::string& name, int& office);
    void see_consult_requests(std::string remote_ip);
    void consult_request(std::string remote_ip);
    void vacation_request(std::string remote_ip);
    void process_requests(std::string remote_ip);
    void decrypt_salary(std::string salary, std::string deductibles, int& salary_int, int& deductibles_int);
    void pdf_data_payment(std::string remote_ip);
    void pdf_data_work(std::string remote_ip);
    void pdf_data_salary(std::string remote_ip);
    void fire_employee(std::string remote_ip);

public:
    data_server();
    ~data_server();
    void wait_for_request();
    void answer_request();
};

#endif // DATA_SERVER_H
