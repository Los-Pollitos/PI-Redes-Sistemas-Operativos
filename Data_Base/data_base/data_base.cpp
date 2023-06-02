/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "data_base.h"


data_base::data_base() {
    this->base = QSqlDatabase::addDatabase("QSQLITE");
    this->base.setDatabaseName("data.db");
    if (! this->base.open()) {
        qDebug() << "[BASE_DATOS] Fallo al conectar";
    } else {
        qDebug() << "[BASE_DATOS] Conexión existosa";
    }
}

data_base::~data_base() {
}

void data_base::add_office(int id, std::string name) {
    QString office_str("CREATE TABLE IF NOT EXISTS offices (id INTEGER, name TEXT)");
    QSqlQuery office_table;
    if (!office_table.exec(office_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla: " << office_table.lastError();
        return;
    }

    QSqlQuery new_office;
    new_office.prepare("INSERT INTO offices (id, name) VALUES (:id, :name)");
    new_office.bindValue(":id", id);
    new_office.bindValue(":name", QString::fromStdString(name));
    if (!new_office.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando sucursal: " << new_office.lastError();
    }
}


void data_base::add_employee(std::string user, std::string name, std::string id
                            , std::string phone_number, std::string email
                            , int office_id, char roles, int available_vacations
                            , int last_laboral_data) {
    QSqlQuery new_employee;
    new_employee.prepare("INSERT INTO employees (user,name,id,phone_number,email,office_id,roles,available_vacations,last_laboral_data) VALUES (:user,:name,:id,:phone_number,:email,:office_id,:roles,:available_vacations,:last_laboral_data)");
    new_employee.bindValue(":user", QString::fromStdString(user));
    new_employee.bindValue(":name", QString::fromStdString(name));
    new_employee.bindValue(":id", QString::fromStdString(id));
    new_employee.bindValue(":phone_number", QString::fromStdString(phone_number));
    new_employee.bindValue(":email", QString::fromStdString(email));
    new_employee.bindValue(":office_id", office_id);
    new_employee.bindValue(":roles", roles);
    new_employee.bindValue(":available_vacations", available_vacations);
    new_employee.bindValue(":last_laboral_data", last_laboral_data);
    if(!new_employee.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando empleado: " << new_employee.lastError();
    }
}

void data_base::add_request(std::string user, int solved, int day_request
                            , int month_request, int year_request
                            ,int day_answer, int month_answer, int year_answer, int type
                            ,int request_id_vac, int day_vac, int month_vac, int year_vac
                            , int shift_vac, int proof_type, std::string content_proof
                            , std::string user_signing_boss_proof) {
    QSqlQuery new_request;
    new_request.prepare("INSERT INTO requests (user,solved,day_request,month_request,year_request,day_answer,month_answer,year_answer,type,request_id_vac,day_vac,month_vac,year_vac,shift_vac,proof_type,content_proof,user_signing_boss_proof) VALUES (:user,:solved,:day_request,:month_request,:year_request,:day_answer,:month_answer,:year_answer,:type,:request_id_vac,:day_vac,:month_vac,:year_vac,:shift_vac,:proof_type,:content_proof,user_signing_boss_proof)");
    new_request.bindValue(":user", QString::fromStdString(user));
    new_request.bindValue(":solved", solved);
    new_request.bindValue(":day_request", day_request);
    new_request.bindValue(":month_request", month_request);
    new_request.bindValue(":year_request", year_request);
    new_request.bindValue(":day_answer", day_answer);
    new_request.bindValue(":month_answer", month_answer);
    new_request.bindValue(":year_answer", year_answer);
    new_request.bindValue(":type", type);
    new_request.bindValue(":request_id_vac", request_id_vac);
    new_request.bindValue(":day_vac", day_vac);
    new_request.bindValue(":month_vac", month_vac);
    new_request.bindValue(":year_vac", year_vac);
    new_request.bindValue(":shift_vac", shift_vac);
    new_request.bindValue(":proof_type", proof_type);
    new_request.bindValue(":content_proof", QString::fromStdString(content_proof));
    new_request.bindValue(":user_signing_boss_proof", QString::fromStdString(user_signing_boss_proof));
    if(!new_request.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando solicitud: " << new_request.lastError();
    }
}

void data_base::add_laboral_data(std::string user, int data_id
                                , int start_day, int start_month, int start_year
                                , int end_day, int end_month, int end_year
                                , int gross_salary, int deductibles, std::string job_title) {
    QSqlQuery new_request;
    new_request.prepare("INSERT INTO laboral_datas (user,data_id,start_day,start_month,start_year,end_day,end_month,end_year,gross_salary,deductible,job_title) VALUES (:user,:data_id,:start_day,:start_month,:start_year,:end_day,:end_month,:end_year,:gross_salary,:deductible,:job_title)");
    new_request.bindValue(":user", QString::fromStdString(user));
    new_request.bindValue(":data_id", data_id);
    new_request.bindValue(":start_day", start_day);
    new_request.bindValue(":start_month", start_month);
    new_request.bindValue(":start_year", start_year);
    new_request.bindValue(":end_day", end_day);
    new_request.bindValue(":end_month", end_month);
    new_request.bindValue(":end_year", end_year);
    new_request.bindValue(":gross_salary", gross_salary);
    new_request.bindValue(":deductibles", deductibles);
    new_request.bindValue(":job_title", QString::fromStdString(job_title));
    if(!new_request.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando solicitud: " << new_request.lastError();
    }
}
void data_base::add_record (std::string user, std::string boss_user
                           , int day, int month, int year, std::string annotation) {
    QSqlQuery new_record;
    new_record.prepare("INSERT INTO requests (user,boss_user,day,month,year,annotation) VALUES (:user,:boss_user,:day,:month,:year,:annotation)");
    new_record.bindValue(":user", QString::fromStdString(user));
    new_record.bindValue(":boss_user", QString::fromStdString(boss_user));
    new_record.bindValue(":day", day);
    new_record.bindValue(":month", month);
    new_record.bindValue(":year", year);
    new_record.bindValue(":annotation", QString::fromStdString(annotation));
    if(!new_record.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando anotación: " << new_record.lastError();
    }
}

std::string data_base::consult_office_name(int id) {
    std::string office_name = "\0";
    QSqlQuery consult_office;
    consult_office.prepare("SELECT name FROM offices WHERE id = (:id)");
    consult_office.bindValue(":id", id);

    if (consult_office.exec() && consult_office.next()){
        office_name = consult_office.value(0).toString().toStdString();

        // TODO(nosotros): borrar
        qDebug() << "[DB] Producto existe y tiene precio: " << office_name;
    }
    return office_name;
}
