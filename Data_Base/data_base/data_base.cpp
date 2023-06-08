/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "data_base.h"
#include <iostream>

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
data_base::~data_base() {
}

char data_base::get_rol(std::string user, int & error) {
    QSqlQuery consult_role;
    char result = '\0';
    std::cout << "me pidieron el rol de " << user << std::endl;
    consult_role.prepare("SELECT roles FROM employees WHERE user = (:user)");
    consult_role.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_role.exec() && consult_role.next()){
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
        actual_data = consult_actual_data.value(0).toString().toStdString()[0];
    }

    consult_salary.prepare("SELECT gross_salary FROM employees WHERE user = (:user) AND data_id = (:actual_data)");
    consult_salary.bindValue(":user", QString::fromStdString(user));
    consult_salary.bindValue(":actual_data", QString::number(actual_data));
    // If a match was found
    if (consult_salary.exec() && consult_salary.next()) {
        result = consult_salary.value(0).toString().toStdString()[0];
    }

    return result;
}


// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
// TODO(nosotros): Ver si cambiar char por string, porque lo saca mal
void data_base::add_employee(std::string user, std::string name, std::string id
                            , std::string phone_number, std::string email
                            , int office_id, char roles, int available_vacations
                            , int last_laboral_data) {
    // Create the employee table if not created
    QString employee_str("CREATE TABLE IF NOT EXISTS employees (user TEXT, name TEXT, id TEXT, phone_number TEXT, email TEXT, office_id INTEGER, roles TEXT, available_vacations INTEGER, last_laboral_data INTEGER)");
    QSqlQuery employee_table;
    if (!employee_table.exec(employee_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de empleados: " << employee_table.lastError();
        return;
    }
    // Add the new employee
    QSqlQuery new_employee;
    new_employee.prepare("INSERT INTO employees (user, name, id, phone_number, email, office_id, roles, available_vacations, last_laboral_data) VALUES (:user, :name, :id, :phone_number, :email, :office_id, :roles, :available_vacations, :last_laboral_data)");
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

// TODO(nosotros): DOCUMENTAR
void data_base::add_request(std::string user,int solved, int day_request
                            , int month_request, int year_request
                            ,int day_answer, int month_answer, int year_answer, int type
                            ,int request_id_vac, int day_vac, int month_vac, int year_vac
                            , int shift_vac, int proof_type, std::string content_proof
                            , std::string user_signing_boss_proof) {
    // Create the request table if not created
    QString request_str("CREATE TABLE IF NOT EXISTS requests (user TEXT, id INTEGER, solved INTEGER, day_request INTEGER, month_request INTEGER, year_request INTEGER, day_answer INTEGER, month_answer INTEGER, year_answer INTEGER, type INTEGER, request_id_vac INTEGER, day_vac INTEGER, month_vac INTEGER, year_vac INTEGER, shift_vac INTEGER, proof_type INTEGER, content_proof TEXT, user_signing_boss_proof TEXT)");
    QSqlQuery request_table;
    if (!request_table.exec(request_str)) {
        qDebug() << "[BASE_DATOS] Error al crear la tabla de solicitudes: " << request_table.lastError();
        return;
    }
    // Add the new request
    QSqlQuery new_request;
    new_request.prepare("INSERT INTO requests (user, id, solved, day_request, month_request, year_request, day_answer, month_answer, year_answer, type, request_id_vac, day_vac, month_vac, year_vac, shift_vac, proof_type, content_proof, user_signing_boss_proof) VALUES (:user, :id, :solved, :day_request, :month_request, :year_request, :day_answer, :month_answer, :year_answer, :type, :request_id_vac, :day_vac, :month_vac, :year_vac, :shift_vac, :proof_type, :content_proof, :user_signing_boss_proof)");
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
    ++this->request_count;
}

// TODO(nosotros): DOCUMENTAR
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


    // TODO(Angie): borrar
    std::cout << "laboral_data agregada: " << user << "," << this->laboral_count << std::endl;

    return this->laboral_count++;
}

// TODO(nosotros): DOCUMENTAR
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
    ++ this->record_count;
}

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
int data_base::consult_employee_office(std::string user) {
    int result = -1;
    QSqlQuery consult_employee;
    consult_employee.prepare("SELECT office_id FROM employees WHERE user = (:user)");
    consult_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        // TODO(nosotros): DESCIFRAR
        result = consult_employee.value(0).toInt();
    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

// TODO(nosotros): DOCUMENTAR
std::string data_base::consult_employee_data(std::string user) {
    std::string result = "";
    bool is_number = true;
    QSqlQuery consult_employee;
    consult_employee.prepare("SELECT name, id, phone_number, email, office_id, roles, available_vacations, last_laboral_data FROM employees WHERE user = (:user)");
    consult_employee.bindValue(":user", QString::fromStdString(user));
    // If a match was found
    if (consult_employee.exec() && consult_employee.next()) {
        for (int i = 0; i < 8; ++i) {
            switch(i) {
                case 0:  // name
                case 1:  // identification
                case 2:  // phone_number
                case 3:  // email
                case 4:  // office ID TODO(Angie): considerar name
                case 5:  // roles
                case 6:  // available vacations
                    result += consult_employee.value(i).toString().toStdString() += ",";
                    break;
                case 7:  // laboral_data
                    //TODO(angie) borrar cout
                    // std::cout << "voy a consult laboral data y tengo: " << user << "y  id" << consult_employee.value(i).toInt(&is_number)<< std::endl;
                    result += this->consult_laboral_data(user, consult_employee.value(i).toInt(&is_number));  // TODO(Angie)
                    break;
            }
        }

        // TODO(Angie)
        result[result.length()-1] = '\0';

    } else {
        qDebug() << "[BASE_DATOS] Error buscando el usuario: " << QString::fromStdString(user);
    }
    return result;
}

// TODO(nosotros): documentar
std::string data_base::consult_laboral_data(std::string user, int data_id) {
    std::string result = "\0";
    QSqlQuery consult_laboral_data;
    consult_laboral_data.prepare("SELECT * FROM laboral_datas WHERE user = (:user) AND data_id = (:data_id)");
    consult_laboral_data.bindValue(":user", QString::fromStdString(user));
    consult_laboral_data.bindValue(":data_id", data_id);
    // If a match was found
    if (consult_laboral_data.exec() && consult_laboral_data.next()) {
        for (int i = 8; i < 11; ++i) {
            result += consult_laboral_data.value(i).toString().toStdString();
            result+= ",";
        }
    } else {
        qDebug() << "[BASE_DATOS] Error con los datos laborales #" << data_id << "del usuario:" << QString::fromStdString(user);
    }
    std::cout << "voy a retornar en consult laboral data " << result << std::endl;
    return result;
}

// TODO(nosotros): documentar
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
void data_base::delete_user_from_table(std::string user, std::string table) {
    QSqlQuery delete_from_table;
    std::string command("DELETE FROM " + table + " WHERE user = (:user)");
    delete_from_table.prepare(QString::fromStdString(command));
    delete_from_table.bindValue(":user", QString::fromStdString(user));
    if (!delete_from_table.exec()) {
        qDebug() << "[BASE_DATOS] Error borrando al usuario: " << QString::fromStdString(user) << " de la tabla " << QString::fromStdString(table);
    }
}

// TODO(nosotros): DOCUMENTAR
void data_base::delete_user(std::string user) {
    this->delete_user_from_table(user, "employees");
    this->delete_user_from_table(user, "requests");
    this->delete_user_from_table(user, "laboral_datas");
    this->delete_user_from_table(user, "records");
}

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
bool data_base::set_end_date_laboral_data(std::string user, int day, int month, int year) {
    bool success = true;
    int data_id = this->consult_employee_office(user);
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

// TODO(nosotros): DOCUMENTAR
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

// TODO(nosotros): DOCUMENTAR
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
