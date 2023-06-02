/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <string>

class data_base {
  private:
    QSqlDatabase base;

  public:
    data_base();
    ~data_base();
    void add_office(int id, std::string name);
    void add_employee(std::string user, std::string name, std::string id
                      , std::string phone_number, std::string email
                      , int office_id, char roles, int available_vacations
                      , int last_laboral_data);
    void add_request(std::string user, int solved, int day_request, int month_request, int year_request
                     ,int day_answer, int month_answer, int year_answer, int type
                     ,int request_id_vac, int day_vac, int month_vac, int year_vac
                     , int shift_vac, int proof_type, std::string content_proof
                     , std::string user_signing_boss_proof);
    void add_laboral_data(std::string user, int data_id
                          , int start_day, int start_month, int start_year
                          , int end_day, int end_month, int end_year
                          , int gross_salary, int deductibles, std::string job_title);
    void add_record (std::string user, std::string boss_user
                    , int day, int month, int year, std::string annotation);

    std::string consult_office_name(int id);
};

#endif // DATA_BASE_H
