/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef DATA_BASE_H
#define DATA_BASE_H

#define PENDING 0
#define ACCEPTED 1
#define DENIED 2

#define VACATION 0
#define PROOF 1

#define PAYMENT_PROOF_T 0
#define WORK_PROOF_T 1
#define SALARY_PROOF_T 2

#define MORNING_SHIFT 1
#define EVENING_SHIFT 2

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <string>

class data_base {
  private:
    // Attributes
    QSqlDatabase base;
    int record_count;
    int laboral_count;
    int request_count;

    // Methods
    void delete_user_from_table(std::string table, std::string user);
    bool verify_office_id(int office);
    std::string request_type(int type, int proof_type);
    std::string request_status(int solved);

  public:
    data_base();
    ~data_base();
    void add_office(int id, std::string name);
    void add_employee(std::string user, std::string name, std::string id
                      , std::string phone_number, std::string email
                      , int office_id, char roles, int available_vacations
                      , int shift_available, int last_laboral_data);
    void add_request(std::string user, int solved, int day_request, int month_request, int year_request
                     ,int day_answer, int month_answer, int year_answer, int type
                     , std::string vacations, int proof_type, std::string content_proof
                     , std::string user_signing_boss_proof);
    int add_laboral_data(std::string user
                          , int start_day, int start_month, int start_year
                          , int end_day, int end_month, int end_year
                          , int gross_salary, int deductibles, std::string job_title);
    void add_record (std::string user, int day, int month, int year, std::string annotation);
    std::string consult_office_name(int id);
    int consult_employee_office(std::string user);
    std::string consult_employee_data(std::string user);
    std::string consult_laboral_data(std::string user, int data_id);
    std::string consult_employees_of_an_office(int office_id);
    char get_rol(std::string user, int & error);
    int get_salary(std::string user);
    int get_deductibles(std::string user);
    std::string get_name(std::string user);
    std::string get_id(std::string user);
    void delete_user(std::string user);
    bool user_exists(std::string user);
    bool change_phone(std::string user, std::string phone);
    bool change_email(std::string user, std::string email);
    bool change_office(std::string user, int office);
    bool change_roles(std::string user, char roles);
    bool change_vacations(std::string user, int vacations);
    bool change_shift(std::string user, int shift_available);
    bool set_end_date_laboral_data(std::string user, int day, int month, int year);
    bool change_last_laboral_data(std::string user, int last_laboral_data);
    std::string consult_process_requests_of_office(int office);
    std::string consult_requests(std::string user);
    std::string consult_request(int id, int type);
    std::string consult_records(std::string user);
    std::string consult_record(int id);
    std::string get_available_vacations(std::string user);
    bool change_request_solved(int id, int solved, int day_answer, int month_answer
                               , int year_answer, std::string user_signing_boss_proof);
    std::string get_request_date_signing(int id);
    std::string get_pay_data(std::string user, int laboral_data);
    std::string get_actual_laboral_data(std::string user);
    std::string consult_laboral_datas(std::string user);
};

#endif // DATA_BASE_H
