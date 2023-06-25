/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "data_base.h"
#include <iostream>
#include <vector>

#include <locale>

data_base::data_base() {
    this->base = QSqlDatabase::addDatabase("QSQLITE");
    this->base.setDatabaseName("data.db");
    if (!this->base.open()) {
        qDebug() << "[BASE_DATOS] Fallo al conectar";
    } else {
        qDebug() << "[BASE_DATOS] Conexión existosa";
    }

    QSqlQuery data_table;
    if (!data_table.exec(QString("DROP TABLE IF EXISTS offices"))) {
        qDebug() << "[BASE_DATOS] Error al borrar offices" << data_table.lastError();
    }
    if (!data_table.exec(QString("DROP TABLE IF EXISTS employees"))) {
        qDebug() << "[BASE_DATOS] Error al borrar employees" << data_table.lastError();
    }
    if (!data_table.exec(QString("DROP TABLE IF EXISTS requests"))) {
        qDebug() << "[BASE_DATOS] Error al borrar requests" << data_table.lastError();
    }
    if (!data_table.exec(QString("DROP TABLE IF EXISTS laboral_datas"))) {
        qDebug() << "[BASE_DATOS] Error al borrar laboral datas" << data_table.lastError();
    }
    if (!data_table.exec(QString("DROP TABLE IF EXISTS records"))) {
        qDebug() << "[BASE_DATOS] Error al borrar records" << data_table.lastError();
    }
}

data_base::~data_base() {
}

char data_base::get_rol(std::string user, int & error) {
    QSqlQuery consult_role;
    char result = '\0';
    consult_role.prepare("SELECT roles FROM employees WHERE user = (:user)");
    consult_role.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_role.exec() && consult_role.next()){
        error = 1;
        result = std::stoi(consult_role.value(0).toString().toStdString());
    } else {
        error = -1;
    }
    return result;
}

int data_base::get_salary(std::string user) {
    QSqlQuery consult_actual_data;
    QSqlQuery consult_salary;
    int actual_data = 0;
    int result = 0;
    consult_actual_data.prepare("SELECT last_laboral_data FROM employees WHERE user = (:user)");
    consult_actual_data.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_actual_data.exec() && consult_actual_data.next()) {
        actual_data =  std::stoi(consult_actual_data.value(0).toString().toStdString());
    }

    consult_salary.prepare("SELECT gross_salary FROM laboral_datas WHERE user = (:user) AND data_id = (:actual_data)");
    consult_salary.bindValue(":user", QString::fromStdString(user));
    consult_salary.bindValue(":actual_data", actual_data);
    // If a match was found
    if (consult_salary.exec() && consult_salary.next()) {
        result = std::stoi(consult_salary.value(0).toString().toStdString());
    } else {
        qDebug() << "[BASE_DATOS] Error con los datos laborales #" << actual_data << "del usuario:" << QString::fromStdString(user);
    }

    return result;
}

int data_base::get_deductibles(std::string user) {
    QSqlQuery consult_actual_data;
    QSqlQuery consult_deductibles;
    int actual_data = 0;
    int result = 0;
    consult_actual_data.prepare("SELECT last_laboral_data FROM employees WHERE user = (:user)");
    consult_actual_data.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_actual_data.exec() && consult_actual_data.next()) {
        actual_data =  std::stoi(consult_actual_data.value(0).toString().toStdString());
    }

    consult_deductibles.prepare("SELECT deductibles FROM laboral_datas WHERE user = (:user) AND data_id = (:actual_data)");
    consult_deductibles.bindValue(":user", QString::fromStdString(user));
    consult_deductibles.bindValue(":actual_data", actual_data);
    // If a match was found
    if (consult_deductibles.exec() && consult_deductibles.next()) {
        result = std::stoi(consult_deductibles.value(0).toString().toStdString());
    } else {
        qDebug() << "[BASE_DATOS] Error con los datos laborales #" << actual_data << "del usuario:" << QString::fromStdString(user);
    }

    return result;
}

std::string data_base::get_name(std::string user){
    QSqlQuery consult_name;
    std::string result = "";
    consult_name.prepare("SELECT name FROM employees WHERE user = (:user)");
    consult_name.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_name.exec() && consult_name.next()) {
        result =  consult_name.value(0).toString().toStdString();
    } else {
        qDebug() << "[BASE_DATOS] Error con el id del usuario:" << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::get_id(std::string user){
    QSqlQuery consult_id;
    std::string result = "";
    consult_id.prepare("SELECT id FROM employees WHERE user = (:user)");
    consult_id.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_id.exec() && consult_id.next()) {
        result =  consult_id.value(0).toString().toStdString();
    } else {
        qDebug() << "[BASE_DATOS] Error con el id del usuario:" << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::get_available_vacations(std::string user) {
    std::string result = "";
    int container = -1;
    QSqlQuery consult;
    consult.prepare("SELECT available_vacations, shift_available FROM employees WHERE user = (:user)");
    consult.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult.exec() && consult.next()) {
        container = consult.value(0).toInt();
        result += std::to_string(container);
        result += '.';
        container = consult.value(1).toInt();
        if (container == 1) {
            result += '5';
        } else {
            result += std::to_string(container);
        }
    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

void data_base::add_office(int id, std::string name) {
    QString office_str("CREATE TABLE IF NOT EXISTS offices (id INTEGER, name TEXT)");
    QSqlQuery office_table;
    if (!office_table.exec(office_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de oficinas: " << office_table.lastError();
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
                            , int shift_available, int last_laboral_data) {
    // Create the employee table if not created
    QString employee_str("CREATE TABLE IF NOT EXISTS employees (user TEXT, name TEXT, id TEXT, phone_number TEXT, email TEXT, office_id INTEGER, roles TEXT, available_vacations INTEGER, shift_available INTEGER, last_laboral_data INTEGER)");
    QSqlQuery employee_table;
    if (!employee_table.exec(employee_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de empleados: " << employee_table.lastError();
        return;
    }
    // Add the new employee
    QSqlQuery new_employee;
    new_employee.prepare("INSERT INTO employees (user, name, id, phone_number, email, office_id, roles, available_vacations, shift_available, last_laboral_data) VALUES (:user, :name, :id, :phone_number, :email, :office_id, :roles, :available_vacations, :shift_available, :last_laboral_data)");
    new_employee.bindValue(":user", QString::fromStdString(user));
    new_employee.bindValue(":name", QString::fromStdString(name));
    new_employee.bindValue(":id", QString::fromStdString(id));
    new_employee.bindValue(":phone_number", QString::fromStdString(phone_number));
    new_employee.bindValue(":email", QString::fromStdString(email));
    new_employee.bindValue(":office_id", office_id);
    new_employee.bindValue(":roles", roles);
    new_employee.bindValue(":available_vacations", available_vacations);
    new_employee.bindValue(":shift_available", shift_available);
    new_employee.bindValue(":last_laboral_data", last_laboral_data);
    if(!new_employee.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando empleado: " << new_employee.lastError();
    }
}

void data_base::add_request(std::string user,int solved, int day_request
                            , int month_request, int year_request
                            ,int day_answer, int month_answer, int year_answer, int type
                            ,std::string vacations, int proof_type, std::string content_proof
                            , std::string user_signing_boss_proof) {
    // Create the request table if not created
    QString request_str("CREATE TABLE IF NOT EXISTS requests (user TEXT, id INTEGER, solved INTEGER, day_request INTEGER, month_request INTEGER, year_request INTEGER, day_answer INTEGER, month_answer INTEGER, year_answer INTEGER, type INTEGER, vacations TEXT, proof_type INTEGER, content_proof TEXT, user_signing_boss_proof TEXT)");
    QSqlQuery request_table;
    if (!request_table.exec(request_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de solicitudes: " << request_table.lastError();
        return;
    }
    // Add the new request
    QSqlQuery new_request;
    new_request.prepare("INSERT INTO requests (user, id, solved, day_request, month_request, year_request, day_answer, month_answer, year_answer, type, vacations, proof_type, content_proof, user_signing_boss_proof) VALUES (:user, :id, :solved, :day_request, :month_request, :year_request, :day_answer, :month_answer, :year_answer, :type, :vacations, :proof_type, :content_proof, :user_signing_boss_proof)");
    new_request.bindValue(":user", QString::fromStdString(user));
    new_request.bindValue(":id", this->request_count);
    new_request.bindValue(":solved", solved);
    new_request.bindValue(":day_request", day_request);
    new_request.bindValue(":month_request", month_request);
    new_request.bindValue(":year_request", year_request);
    new_request.bindValue(":day_answer", day_answer);
    new_request.bindValue(":month_answer", month_answer);
    new_request.bindValue(":year_answer", year_answer);
    new_request.bindValue(":type", type);
    new_request.bindValue(":vacations", QString::fromStdString(vacations));
    new_request.bindValue(":proof_type", proof_type);
    new_request.bindValue(":content_proof", QString::fromStdString(content_proof));
    new_request.bindValue(":user_signing_boss_proof", QString::fromStdString(user_signing_boss_proof));
    if(!new_request.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando solicitud: " << new_request.lastError();
    }
    ++this->request_count;
}

int data_base::add_laboral_data(std::string user
                                , int start_day, int start_month, int start_year
                                , int end_day, int end_month, int end_year
                                , int gross_salary, int deductibles, std::string job_title) {
    // Create the laboral data table if not created
    QString laboral_data_str("CREATE TABLE IF NOT EXISTS laboral_datas (user TEXT, data_id INTEGER, start_day INTEGER, start_month INTEGER, start_year INTEGER, end_day INTEGER, end_month INTEGER, end_year INTEGER, gross_salary INTEGER, deductibles INTEGER, job_title TEXT)");
    QSqlQuery laboral_data_table;
    if (!laboral_data_table.exec(laboral_data_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de datos laborales: " << laboral_data_table.lastError();
        return -1;
    }
    // Add the new laboral data
    QSqlQuery new_laboral_data;
    new_laboral_data.prepare("INSERT INTO laboral_datas (user, data_id, start_day, start_month, start_year, end_day, end_month, end_year, gross_salary, deductibles, job_title) VALUES (:user, :data_id, :start_day, :start_month, :start_year, :end_day, :end_month, :end_year, :gross_salary, :deductibles, :job_title)");
    new_laboral_data.bindValue(":user", QString::fromStdString(user));
    new_laboral_data.bindValue(":data_id", this->laboral_count);
    new_laboral_data.bindValue(":start_day", start_day);
    new_laboral_data.bindValue(":start_month", start_month);
    new_laboral_data.bindValue(":start_year", start_year);
    new_laboral_data.bindValue(":end_day", end_day);
    new_laboral_data.bindValue(":end_month", end_month);
    new_laboral_data.bindValue(":end_year", end_year);
    new_laboral_data.bindValue(":gross_salary", gross_salary);
    new_laboral_data.bindValue(":deductibles", deductibles);
    new_laboral_data.bindValue(":job_title", QString::fromStdString(job_title));
    if(!new_laboral_data.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando datos laborales: " << new_laboral_data.lastError();
    }

    return this->laboral_count++;
}

void data_base::add_record(std::string user, int day, int month, int year, std::string annotation) {
    // Create the record table if not created
    QString record_str("CREATE TABLE IF NOT EXISTS records (user TEXT, id INTEGER, day INTEGER, month INTEGER, year INTEGER, annotation TEXT)");
    QSqlQuery record_table;
    if (!record_table.exec(record_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de anotaciones: " << record_table.lastError();
        return;
    }
    // Add the new record
    QSqlQuery new_record;
    new_record.prepare("INSERT INTO records (user, id, day, month, year, annotation) VALUES (:user, :id, :day, :month, :year, :annotation)");
    new_record.bindValue(":user", QString::fromStdString(user));
    new_record.bindValue(":id", this->record_count);
    new_record.bindValue(":day", day);
    new_record.bindValue(":month", month);
    new_record.bindValue(":year", year);
    new_record.bindValue(":annotation", QString::fromStdString(annotation));
    if(!new_record.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando anotación: " << new_record.lastError();
    }
    ++this->record_count;
}

std::string data_base::consult_office_name(int id) {
    std::string office_name = "\0";
    QSqlQuery consult_office;
    consult_office.prepare("SELECT name FROM offices WHERE id = (:id)");
    consult_office.bindValue(":id", id);
    // If a match was found
    if (consult_office.exec() && consult_office.next()){
        office_name = consult_office.value(0).toString().toStdString();
    }
    return office_name;
}

int data_base::consult_employee_office(std::string user) {
    int result = -1;
    QSqlQuery consult_employee;
    consult_employee.prepare("SELECT office_id FROM employees WHERE user = (:user)");
    consult_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        result = consult_employee.value(0).toInt();
    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

int data_base::get_laboral_count() {
    return this->laboral_count;
}

int data_base::consult_last_laboral_data(std::string user) {
    int result = -1;
    QSqlQuery consult_employee;
    consult_employee.prepare("SELECT last_laboral_data FROM employees WHERE user = (:user)");
    consult_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        result = consult_employee.value(0).toInt();
    } else {
        qDebug() << "[BASE_DATOS] Error con el usuario al buscar la última entrada laboral:" << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::consult_employee_data(std::string user) {
    std::string result = "";
    bool is_number = true;
    QSqlQuery consult_employee;
    char temp_result;
    consult_employee.prepare("SELECT name, id, phone_number, email, office_id, roles, available_vacations, shift_available, last_laboral_data FROM employees WHERE user = (:user)");
    consult_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        for (int i = 0; i < 9; ++i) {
            switch(i) {
                case 0:  // name
                case 1:  // identification
                case 2:  // phone_number
                case 3:  // email
                case 4:  // office ID TODO(Angie): considerar name
                case 6:  // available vacations
                case 7:  // shift_available
                    result += consult_employee.value(i).toString().toStdString() += ",";
                    break;
                case 5:  // roles
                    temp_result = std::stoi(consult_employee.value(i).toString().toStdString());
                    result += temp_result;
                    result += ",";
                    break;
                case 8:  // laboral_data
                    result += this->consult_laboral_data(user, consult_employee.value(i).toInt(&is_number));
                    break;
            }
        }
        result[result.length()-1] = '\0';

    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::consult_laboral_data(std::string user, int data_id) {
    security security_manager;
    std::string result = "\0";
    std::string salary_encrypt = "\0";
    std::string deductibles_encrypt = "\0";
    int salary = 0;
    int deductibles = 0;
    QSqlQuery consult_laboral_data;

    consult_laboral_data.prepare("SELECT * FROM laboral_datas WHERE user = (:user) AND data_id = (:data_id)");
    consult_laboral_data.bindValue(":user", QString::fromStdString(user));
    consult_laboral_data.bindValue(":data_id", data_id);

    // If a match was found
    if (consult_laboral_data.exec() && consult_laboral_data.next()) {
        for (int i = 8; i < 11; ++i) {
            switch(i) {
                case 8:  // salary
                    salary = consult_laboral_data.value(i).toInt();
                    this->encrypt(salary_encrypt, salary);
                    result += salary_encrypt + ",";
                    break;
                case 9:  // deductibles
                    deductibles = consult_laboral_data.value(i).toInt();
                    this->encrypt(deductibles_encrypt, deductibles);
                    result += deductibles_encrypt + ",";
                    break;
                case 10:  // job_title
                    result += consult_laboral_data.value(i).toString().toStdString();
                    result += ",";
                    break;
            }
        }
    } else {
        qDebug() << "[BASE_DATOS] Error con los datos laborales #" << data_id << "del usuario:" << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::consult_employees() {
    std::string result = "";
    QSqlQuery consult_employee;

    consult_employee.prepare("SELECT * FROM employees");

    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        do {
            result += consult_employee.value(0).toString().toStdString() += ",";
        } while (consult_employee.next());
        result[result.length()-1] = '\0';  // there was an extra ','
    } else {
        qDebug() << "[BASE_DATOS] Error buscando todos los empleados";
    }
    return result;
}

std::string data_base::consult_employees_of_an_office(int office_id) {
    std::string result = "";
    QSqlQuery consult_employee;

    consult_employee.prepare("SELECT * FROM employees WHERE office_id = (:office_id)");
    consult_employee.bindValue(":office_id", office_id);

    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        do {
           result += consult_employee.value(0).toString().toStdString() += ",";
        } while (consult_employee.next());
        result[result.length()-1] = '\0';  // there was an extra ','
    } else {
        qDebug() << "[BASE_DATOS] Error buscando el la oficina: " << office_id;
    }
    return result;
}

bool data_base::user_exists(std::string user) {
    bool result = false;
    QSqlQuery find_employee;
    find_employee.prepare("SELECT roles FROM employees WHERE user = (:user)");
    find_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (find_employee.exec() && find_employee.next()) {
        // Result is true
        result = true;
    }
    return result;
}

void data_base::delete_user_from_table(std::string user, std::string table) {
    QSqlQuery delete_from_table;
    std::string command("DELETE FROM " + table + " WHERE user = (:user)");
    delete_from_table.prepare(QString::fromStdString(command));
    delete_from_table.bindValue(":user", QString::fromStdString(user));
    if (!delete_from_table.exec()) {
        qDebug() << "[BASE_DATOS] Error borrando al usuario: " << QString::fromStdString(user) << " de la tabla " << QString::fromStdString(table);
    }
}

void data_base::delete_user(std::string user) {
    this->delete_user_from_table(user, "employees");
    this->delete_user_from_table(user, "requests");
    this->delete_user_from_table(user, "laboral_datas");
    this->delete_user_from_table(user, "records");
}

bool data_base::change_phone(std::string user, std::string phone) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET phone_number = (:phone_number) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":phone_number", QString::fromStdString(phone));
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando el teléfono de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

bool data_base::change_email(std::string user, std::string email) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET email = (:email) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":email", QString::fromStdString(email));
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando el correo de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

bool data_base::change_office(std::string user, int office) {
    bool success = true;
    if (this->verify_office_id(office)) {
        QSqlQuery modify_user;
        modify_user.prepare("UPDATE employees SET office_id = (:office_id) WHERE user = (:user)");
        modify_user.bindValue(":user", QString::fromStdString(user));
        modify_user.bindValue(":office_id", office);
        if (!modify_user.exec()) {
            qDebug() << "[BASE_DATOS] Error modificando la sucursal de " << QString::fromStdString(user);
            success = false;
        }
    } else {
        success = false;
    }
    return success;
}

bool data_base::change_roles(std::string user, char roles) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET roles = (:roles) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":roles", roles);
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando los roles de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

bool data_base::change_vacations(std::string user, int vacations) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET available_vacations = (:available_vacations) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":available_vacations", vacations);
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando las vacaiones disponibles de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

bool data_base::change_shift(std::string user, int shift_available) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET shift_available = (:shift_available) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":shift_available", shift_available);
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando los turnos disponibles de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

bool data_base::set_end_date_laboral_data(std::string user, int day, int month, int year) {
    bool success = true;
    int data_id = this->consult_last_laboral_data(user);
    QSqlQuery modify_user;

    modify_user.prepare("UPDATE laboral_datas SET end_day = (:end_day), end_month = (:end_month), end_year = (:end_year) WHERE user = (:user) AND data_id = (:data_id)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":end_day", day);
    modify_user.bindValue(":end_month", month);
    modify_user.bindValue(":end_year", year);
    modify_user.bindValue(":data_id", data_id);
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando los datos laborales #" << data_id << " de " << QString::fromStdString(user);
        success = false;
    }

    return success;
}

bool data_base::verify_office_id(int office) {
    bool result = false;
    QSqlQuery find_office;
    find_office.prepare("SELECT name FROM offices WHERE id = (:id)");
    find_office.bindValue(":id", office);
    // If a match was found
    if (find_office.exec() && find_office.next()) {
        // Result is true
        result = true;
    }
    return result;
}

bool data_base::change_last_laboral_data(std::string user, int last_laboral_data) {
    bool success = true;
    QSqlQuery modify_user;
    modify_user.prepare("UPDATE employees SET last_laboral_data = (:last_laboral_data) WHERE user = (:user)");
    modify_user.bindValue(":user", QString::fromStdString(user));
    modify_user.bindValue(":last_laboral_data", last_laboral_data);
    if (!modify_user.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando la última entrada de datos laborales de " << QString::fromStdString(user);
        success = false;
    }
    return success;
}

std::string data_base::consult_process_requests_of_office(int office_id) {
    std::string result = "";
    QSqlQuery consult_employee;
    std::string employee_consult = this->consult_employees_of_an_office(office_id);
    employee_consult[employee_consult.size() - 1] = ',';
    std::vector<std::string> employee_vector;
    std::string employee = "";
    for(size_t i = 0; i < employee_consult.length(); ++i) {
        if (employee_consult[i] != ',') {
            employee += employee_consult[i];
        } else {  // is the end of the username
            employee_vector.push_back(employee);
            employee = "\0";  // it is cleaned for next username
        }
    }
    for (size_t i = 0; i < employee_vector.size(); ++ i) {
        consult_employee.prepare("SELECT id, type FROM requests WHERE user = (:employee) AND solved = (:solved)");
        consult_employee.bindValue(":employee", QString::fromStdString(employee_vector[i]));
        consult_employee.bindValue(":solved", PENDING);
        // If a match was found
        if (consult_employee.exec() && consult_employee.next()) {
            do {
                result += employee_vector[i]; // employee name
                result += ":";
                result += consult_employee.value(0).toString().toStdString() += ":"; // request id
                result += consult_employee.value(1).toString().toStdString() += ":"; // type
                result += ",";
            } while (consult_employee.next());
        }
    }
    if (result.length() == 0) {
        result = "0";  // no requests are needed to be proccessed
    } else {
        result[result.length()-1] = '\0';  // there was an extra ','
    }
    return result;
}

std::string data_base::consult_requests(std::string user) {
    std::string result = "";
    QSqlQuery consult_requests;

    consult_requests.prepare("SELECT id, solved, type, proof_type FROM requests WHERE user = (:user)");
    consult_requests.bindValue(":user", QString::fromStdString(user));

    // If a match was found
    if (consult_requests.exec() && consult_requests.next()) {
        do {
            result += consult_requests.value(0).toString().toStdString() + "-";  // id
            result += consult_requests.value(2).toString().toStdString() + "-";  // type
            result += this->request_type(consult_requests.value(2).toInt(), consult_requests.value(3).toInt()) + ": ";
            result += this->request_status(consult_requests.value(1).toInt()) += ",";  // status
        } while (consult_requests.next());
        result[result.length()-1] = '\0';  // there was an extra ','
    } else {
        qDebug() << "[BASE_DATOS] Error consultando las solicitudes de: " << user;
    }

    return result;
}

std::string data_base::request_type(int type, int proof_type) {
    std::string result = "\0";

    if (type == VACATION) {
        result = "Vacaciones";
    } else {
        switch(proof_type) {
            case PAYMENT_PROOF_T:
                result += "Constancia de pago";
                break;
            case WORK_PROOF_T:
                result += "Constancia de trabajo";
                break;
            case SALARY_PROOF_T:
                result += "Constancia salarial";
                break;
        }
    }

    return result;
}

std::string data_base::request_status(int solved) {
    std::string result = "\0";
    switch(solved) {
        case PENDING:
            result += "En proceso";
            break;
        case ACCEPTED:
            result += "Aceptada";
            break;
        case DENIED:
            result += "Rechazada";
            break;
    }
    return result;
}

std::string data_base::consult_request(int id, int type) {
    std::string result = "";
    QSqlQuery consult_request;
    QString request_str = "\0";

    if (type == VACATION){
        request_str = "SELECT day_request, month_request, year_request, vacations FROM requests WHERE id = (:id)";
    } else {
        request_str = "SELECT day_request, month_request, year_request, content_proof, user_signing_boss_proof FROM requests WHERE id = (:id)";
    }

    consult_request.prepare(request_str);
    consult_request.bindValue(":id", id);

    // If a match was found
    if (consult_request.exec() && consult_request.next()) {
        result += consult_request.value(0).toString().toStdString() + ",";  // day
        result += consult_request.value(1).toString().toStdString() + ",";  // month
        result += consult_request.value(2).toString().toStdString() + ",";  // year
        result += consult_request.value(3).toString().toStdString();  // content

        if (type != VACATION) {
            result += "," + consult_request.value(4).toString().toStdString();
        } else {
            result[result.length()-1] = '&';
            result += "\0";
        }
    } else {
        qDebug() << "[BASE_DATOS] Error consultando la solicitud #" << id << "de tipo:" << type;
    }

    return result;
}

std::string data_base::consult_records(std::string user) {
    std::string result = "";
    QSqlQuery consult_record;

    consult_record.prepare("SELECT id FROM records WHERE user = (:user)");
    consult_record.bindValue(":user", QString::fromStdString(user));

    // If a match was found
    if (consult_record.exec() && consult_record.next()) {
        do {
            result += this->consult_record(stoi(consult_record.value(0).toString().toStdString())) += "\n";
        } while (consult_record.next());
        result[result.length()-1] = '\0';  // there was an extra ','
    } else {
        qDebug() << "[BASE_DATOS] Error consultando anotaciones de: " << user;
    }

    return result;
}

std::string data_base::consult_record(int id) {
    std::string result = "";
    QSqlQuery consult_record;

    consult_record.prepare("SELECT * FROM records WHERE id = (:id)");
    consult_record.bindValue(":id", id);

    // If a match was found
    if (consult_record.exec() && consult_record.next()) {
        do {
            for (int i = 2; i < 6; ++i) {
                switch (i) {
                    case 2:  // day
                        result += "[" + consult_record.value(i).toString().toStdString();
                        break;
                    case 3:  // month
                        result += "-" + consult_record.value(i).toString().toStdString();
                        break;
                    case 4:  // year
                        result += "-" + consult_record.value(i).toString().toStdString() += "] ";
                        break;
                    case 5:  // annotation
                        result += consult_record.value(i).toString().toStdString();
                        break;
                }
            }
        } while (consult_record.next());
    } else {
        qDebug() << "[BASE_DATOS] Error buscando la anotación #" << id;
    }
    return result;
}

bool data_base::change_request_solved(int id, int solved, int day_answer, int month_answer
                                      , int year_answer, std::string user_signing_boss_proof) {
    bool success = true;
    if (solved) {
        // Used to remove the days from the employee
        QSqlQuery check_vacation;
        check_vacation.prepare("SELECT * FROM requests WHERE id = (:id)");
        check_vacation.bindValue(":id", id);
        if (check_vacation.exec()  && check_vacation.next()) {
            std::string temporal_type = check_vacation.value(9).toString().toStdString();
            if (temporal_type == "0") {
                std::string user = check_vacation.value(0).toString().toStdString();
                double current_vacations = std::stod(this->get_available_vacations(user));
                double remove = this->get_vacations_from_string(check_vacation.value(10).toString().toStdString());
                current_vacations -= remove;
                this->transform_vacations(current_vacations, user);
            }
        } else {
            qDebug() << "[BASE_DATOS] Error modificando las vacaciones";
            success = false;
        }
    }
    if (success) {
        QSqlQuery modify_request;
        modify_request.prepare("UPDATE requests SET solved = (:solved), day_answer = (:day_answer), month_answer = (:month_answer), year_answer = (:year_answer), user_signing_boss_proof = (:user_signing_boss_proof) WHERE id = (:id)");
        modify_request.bindValue(":id", id);
        modify_request.bindValue(":solved", solved);
        modify_request.bindValue(":day_answer", day_answer);
        modify_request.bindValue(":month_answer", month_answer);
        modify_request.bindValue(":year_answer", year_answer);
        modify_request.bindValue(":user_signing_boss_proof", QString::fromStdString(user_signing_boss_proof));
        if (!modify_request.exec()) {
            qDebug() << "[BASE_DATOS] Error modificando la solicitud" << QString::fromStdString(user_signing_boss_proof);
            success = false;
        }
    }
    return success;
}

void data_base::transform_vacations(double current_vacations, std::string user) {
    std::string temp_string = std::to_string(current_vacations);
    std::string vacations = "";
    int shift = 0;
    bool dot_found = false;
    for (size_t i = 0; i < temp_string.size(); ++i) {
        if (temp_string[i] == '.') {
            dot_found = true;
            ++i;
        }
        if (!dot_found) {
            vacations += temp_string[i];
        } else {
            if (temp_string[i] == '5') {
                shift = 1;
            }
        }
    }
    int vacation_number = std::stoi(vacations);
    QSqlQuery modify_vacations;
    modify_vacations.prepare("UPDATE employees SET available_vacations = (:available_vacations), shift_available = (:shift_available) WHERE user = (:user)");
    modify_vacations.bindValue(":available_vacations", vacation_number);
    modify_vacations.bindValue(":shift_available", shift);
    modify_vacations.bindValue(":user", QString::fromStdString(user));
    if (!modify_vacations.exec()) {
        qDebug() << "[BASE_DATOS] Error modificando vacaciones de usuario";
    }
}

double data_base::get_vacations_from_string(std::string vacations) {
    int found_comma = 0;
    std::string temp_string = "";
    for (size_t i = 0; i < vacations.size(); ++i) {
        if (vacations[i] == ',') {
            ++found_comma;
            ++i;
        }
        if (found_comma == 1) {
            temp_string += vacations[i];
        }
    }
    // Save the original global locale
    std::locale original_locale = std::locale::global(std::locale::classic());
    // Create a temporary "C" locale
    std::locale c_locale("C");
    // Set the temporary locale as the global locale
    std::locale::global(c_locale);
    double answer = std::stod(temp_string);
    // Restore the original global locale
    std::locale::global(original_locale);
    return answer;
}

void data_base::encrypt(std::string& to_encript, int from_encrypt) {
    security security_manager;
    std::string buffer = security_manager.encrypt(std::to_string(from_encrypt));
    to_encript = "\0";

    // salary
    for (size_t i = 0; i < buffer.length(); ++i) {
        to_encript += std::to_string((int) buffer[i]);
        to_encript += ".";
    }
}


std::string data_base::get_request_date_signing(int id){
    std::string result = "";
    QSqlQuery consult_request;
    QString request_str = "\0";

    request_str = "SELECT day_answer, month_answer, year_answer, user_signing_boss_proof, user FROM requests WHERE id = (:id)";


    consult_request.prepare(request_str);
    consult_request.bindValue(":id", id);

    // If a match was found
    if (consult_request.exec() && consult_request.next()) {
        result += consult_request.value(0).toString().toStdString() + ",";  // day
        result += consult_request.value(1).toString().toStdString() + ",";  // month
        result += consult_request.value(2).toString().toStdString() + ",";  // year
        result += consult_request.value(3).toString().toStdString() + ",";  // user_signing_boss_proof
        result += consult_request.value(4).toString().toStdString();  // user
    } else {
        qDebug() << "[BASE_DATOS] Error consultando la solicitud #" << id;
    }
    result += "\0";

    return result;
}

std::string data_base::get_pay_data(std::string user, int data_id){
    std::string result = "\0";
    QSqlQuery consult_laboral_data;
    consult_laboral_data.prepare("SELECT gross_salary, deductibles, job_title FROM laboral_datas WHERE user = (:user) AND data_id = (:data_id)");
    consult_laboral_data.bindValue(":user", QString::fromStdString(user));
    consult_laboral_data.bindValue(":data_id", data_id);
    // If a match was found
    if (consult_laboral_data.exec() && consult_laboral_data.next()) {
        result += consult_laboral_data.value(0).toString().toStdString() + ",";  // salary
        result += consult_laboral_data.value(1).toString().toStdString() + ",";  // deductibles
        result += consult_laboral_data.value(2).toString().toStdString() + ",";  // job_title
    } else {
        qDebug() << "[BASE_DATOS] Error con los datos laborales #" << data_id << "del usuario:" << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::get_actual_laboral_data(std::string user) {
    std::string result = "\0";
    QSqlQuery consult_actual_laboral;
    consult_actual_laboral.prepare("SELECT last_laboral_data FROM employees WHERE user = (:user)");
    consult_actual_laboral.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_actual_laboral.exec() && consult_actual_laboral.next()) {
        result = consult_actual_laboral.value(0).toString().toStdString();
    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

std::string data_base::consult_laboral_datas(std::string user) {
    std::string result = "";
    QSqlQuery consult_laboral_data;

    consult_laboral_data.prepare("SELECT * FROM laboral_datas WHERE user = (:user)");
    consult_laboral_data.bindValue(":user", QString::fromStdString(user));

    // If a match was found
    if (consult_laboral_data.exec() && consult_laboral_data.next()) {
        do {
            for (int i = 2; i < 11; ++i) {
                result += consult_laboral_data.value(i).toString().toStdString();
                result += ";";
            }
            result[result.length()-1] = '|';
        } while (consult_laboral_data.next());
    } else {
        qDebug() << "[BASE_DATOS] Error buscando los datos laborales de: " << user;
    }
    return result;
}
