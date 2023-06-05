/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "data_server.h"
#include <iostream>
#include <QFile>

/*
 * @brief Default constructor
*/
data_server::data_server() {
    // Create the data_base
    this->base = new data_base();
    this->load_from_file();
    this->connection = -1;
    this->message_count = 0;

    // TODO(Angie): borrar
    std::cout << "voy a llamar a consult_employees\n";
    std::cout << "Oficina 1 ____________\n";
    this->base->consult_employees_of_an_office(1);
    std::cout << "Oficina 2 ____________\n";
    this->base->consult_employees_of_an_office(2);
    std::cout << "Oficina 3 ____________\n";
    this->base->consult_employees_of_an_office(3);
    std::cout << "Oficina 4 ____________\n";
    this->base->consult_employees_of_an_office(4);
    std::cout << "Oficina 5 ____________\n";
    this->base->consult_employees_of_an_office(5);
}

/*
 * @brief Destructor
*/
data_server::~data_server() {
    delete this->base;
}

// TODO(nosotros): documentar
void data_server::adapt_data(char* data, std::string& new_info, int pos) {
    for (int i = 0; i < DATA_SIZE; ++i){
        data[i] = new_info[i+pos];
    }
    pos -= 1;
}

// TODO(nosotros): documentar
void data_server::find_next(std::string& line, int& pos) {
    int stop = 0;
    for (; pos < (int)line.length() && stop == 0; ++pos) {
        if (line[pos] == ',') {
            stop = 1;
        }
    }
}

// TODO(nosotros): documentar
void data_server::copy_string(std::string& line, std::string& new_line, int from, int to) {
    new_line.resize(to-from);

    for (int i = from; i < to; ++i) {
        new_line[i-from] = line[i];
    }
}

// TODO(nosotros): actualizar documentación
/*
 * @brief Loads the file system from a .txt file containing the necessary
 * login information, creating the image of the file system for future uses.
*/
void data_server::load_from_file() {
    this->load_offices();
    this->load_employees();
    this->load_requests();  // TODO(nosotros): arreglar: no crea la tabla
    this->load_laboral_data();  // TODO(nosotros): arreglar: no crea la tabla
    this->load_records();
}

// TODO(nosotros): documentar
void data_server::load_offices() {
    std::string line = " ";
    std::string partial_line = "!";
    int initial_pos = 0;
    int end_pos = 0;

    int id = 0;
    std::string name = " ";

    QFile office_file("../tables_files/offices.txt");
    if (office_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        line = office_file.readLine().toStdString();  // ignores the header
        while(!office_file.atEnd()) {
            initial_pos = 0;
            end_pos = 1;

            // gets the line of the table
            line = office_file.readLine().toStdString();

            // find the id
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos-1);
            // save the id
            id = stoi(partial_line);

            // find the name
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the name
            this->copy_string(line,name,initial_pos,end_pos-1);

            // add to offices table
            this->base->add_office(id, name);
        }
        office_file.close();
    } else {
        qDebug() << "[SERVIDOR_BASE_DATOS] No se pudo abrir el archivo de offices.txt";
    }
}

// TODO(nosotros): documentar
void data_server::load_employees() {
    std::string line = "\0";
    std::string partial_line = "\0";
    int initial_pos = 0;
    int end_pos = -1;

    std::string user = "\0";
    std::string name = "\0";
    std::string id = "\0";
    std::string phone_number = "\0";
    std::string email = "\0";
    int office_id = 0;
    char roles = '0';
    int available_vacations = 0;
    int last_laboral_data = 0;

    QFile employee_file("../tables_files/employees.txt");

    if (employee_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        employee_file.readLine();   // ignores the header
        while(!employee_file.atEnd()) {
            initial_pos = 0;
            end_pos = 0;

            // gets the line of the table
            line = employee_file.readLine().toStdString();

            // find the user
            this->find_next(line, end_pos);
            // save the user
            this->copy_string(line,user,initial_pos ,end_pos-1);

            // find the name
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the name
            this->copy_string(line,name,initial_pos ,end_pos-1);

            // find the id
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the id
            this->copy_string(line,id,initial_pos ,end_pos-1);

            // find the phone number
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the phone number
            this->copy_string(line,phone_number,initial_pos ,end_pos-1);

            // find the email
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the email
            this->copy_string(line,email,initial_pos ,end_pos-1);

            // find the office_id
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the office_id
            office_id = stoi(partial_line);

            // find the roles
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the roles
            roles = stoi(partial_line);

            // find the available_vacations
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the available_vacations
            available_vacations = stoi(partial_line);

            // find the last_laboral_data
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the last_laboral_data
            last_laboral_data = stoi(partial_line);

            // add to offices table
            this->base->add_employee(user, name, id, phone_number, email, office_id, roles, available_vacations, last_laboral_data);
        }
        employee_file.close();
    }
}

// TODO(nosotros): documentar
void data_server::load_laboral_data() {
    std::string line = "\0";
    std::string partial_line = "\0";
    int initial_pos = 0;
    int end_pos = -1;

    std::string user = "\0";
    int data_id = 0;
    int start_day = 0;
    int start_month = 0;
    int start_year = 0;
    int end_day = 0;
    int end_month = 0;
    int end_year = 0;
    int gross_salary = 0;
    int deductibles = 0;
    std::string job_title = "\0";

    QFile laboral_data_file("../tables_files/laboral_datas.txt");

    if (laboral_data_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        laboral_data_file.readLine();   // ignores the header
        while(!laboral_data_file.atEnd()) {
            initial_pos = 0;
            end_pos = 0;

            // gets the line of the table
            line = laboral_data_file.readLine().toStdString();

            // find the user
            this->find_next(line, end_pos);
            // save the user
            this->copy_string(line,user,initial_pos ,end_pos-1);

            // find the data_id
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the data_id
            data_id = stoi(partial_line);

            // find the start_day
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the start_day
            start_day = stoi(partial_line);

            // find the start_month
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the start_month
            start_month = stoi(partial_line);

            // find the start_year
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the start_year
            start_year = stoi(partial_line);

            // find the end_day
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the end_day
            end_day = stoi(partial_line);

            // find the end_month
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the end_month
            end_month = stoi(partial_line);

            // find the end_year
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the end_year
            end_year = stoi(partial_line);

            // find the gross_salary
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the gross_salary
            gross_salary = stoi(partial_line);

            // find the deductibles
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the deductibles
            deductibles = stoi(partial_line);

            // find the job_title
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the job_title
            this->copy_string(line,job_title,initial_pos ,end_pos-1);

            // add to laboral data table
            this->base->add_laboral_data(user, data_id, start_day, start_month, start_year, end_day
                                         , end_month, end_year, gross_salary, deductibles, job_title);
        }
        laboral_data_file.close();
    }
}

// TODO(nosotros): documentar
void data_server::load_requests() {
    std::string line = "\0";
    std::string partial_line = "\0";
    int initial_pos = 0;
    int end_pos = -1;

    std::string user = "\0";
    int id = 0;
    int solved = 0;
    int day_request = 0;
    int month_request = 0;
    int year_request = 0;
    int day_answer = 0;
    int month_answer = 0;
    int year_answer = 0;
    int type = 0;
    int request_id_vac = 0;
    int day_vac = 0;
    int month_vac = 0;
    int year_vac = 0;
    int shift_vac = 0;
    int proof_type = 0;
    std::string content_proof = "\0";
    std::string user_signing_boss_proof = "\0";

    QFile request_file("../tables_files/requests.txt");

    if (request_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        request_file.readLine();   // ignores the header
        while(!request_file.atEnd()) {
            initial_pos = 0;
            end_pos = 0;

            // gets the line of the table
            line = request_file.readLine().toStdString();

            // find the user
            this->find_next(line, end_pos);
            // save the user
            this->copy_string(line,user,initial_pos ,end_pos-1);

            // find the id
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the id
            id = stoi(partial_line);

            // find if solved
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save if solved
            solved = stoi(partial_line);

            // find the day_request
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the day_request
            day_request = stoi(partial_line);

            // find the month_request
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the month_request
            month_request = stoi(partial_line);

            // find the year_request
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the year_request
            year_request = stoi(partial_line);

            // find the day_answer
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the day_answer
            day_answer = stoi(partial_line);

            // find the month_answer
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the month_answer
            month_answer = stoi(partial_line);

            // find the year_answer
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the year_answer
            year_answer = stoi(partial_line);

            // find the type
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the type
            type = stoi(partial_line);

            // find the request_id_vac
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the request_id_vac
            request_id_vac = stoi(partial_line);

            // find the day_vac
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the day_vac
            day_vac = stoi(partial_line);

            // find the month_vac
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the month_vac
            month_vac = stoi(partial_line);

            // find the year_vac
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the year_vac
            year_vac = stoi(partial_line);

            // find the shift_vac
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the shift_vac
            shift_vac = stoi(partial_line);

            // find the proof_type
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the proof_type
            proof_type = stoi(partial_line);

            // find the content_proof
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the content_proof
            this->copy_string(line,content_proof,initial_pos ,end_pos-1);

            // find the user_signing_boss_proof
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the user_signing_boss_proof
            this->copy_string(line,user_signing_boss_proof,initial_pos ,end_pos-1);

            this->base->add_request(user, id, solved, day_request, month_request, year_request, day_answer
                                    , month_answer, year_answer, type, request_id_vac, day_vac, month_vac
                                    , year_vac, shift_vac, proof_type, content_proof, user_signing_boss_proof);
        }
        request_file.close();
    }
}

// TODO(nosotros): documentar
void data_server::load_records() {
    std::string line = "\0";
    std::string partial_line = "\0";
    int initial_pos = 0;
    int end_pos = -1;

    std::string user = "\0";
    int id = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    std::string annotation = "\0";

    QFile records_file("../tables_files/records.txt");

    if (records_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        records_file.readLine();   // ignores the header
        while(!records_file.atEnd()) {
            initial_pos = 0;
            end_pos = 0;

            // gets the line of the table
            line = records_file.readLine().toStdString();

            // find the user
            this->find_next(line, end_pos);
            // save the user
            this->copy_string(line,user,initial_pos ,end_pos-1);

            // find the id
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the id
            id = stoi(partial_line);

            // find the day
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the day
            day = stoi(partial_line);

            // find the month
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the month
            month = stoi(partial_line);

            // find the year
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the year
            year = stoi(partial_line);

            // find the annotation
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the annotation
            this->copy_string(line,annotation,initial_pos ,end_pos-1);

            // add to records table
            this->base->add_record (user, id, day, month, year, annotation);
        }
        records_file.close();
    }
}

/*
 * @brief The server waits for a request from a client to answer it.
 */
void data_server::wait_for_request() {
    int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in ip;

    memset(&ip, '0', sizeof(ip));
    memset(this->data, '\0', sizeof(this->data));
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = htonl(INADDR_ANY);
    ip.sin_port = htons(PORT);

    bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
    listen(socketServidor, 20);

    sleep(1);
    socklen_t l = sizeof(this->ipRemoto);
    std::cout << std::endl << "[SERVIDOR_BASE_DATOS ESCUCHANDO]" << std::endl;
    // TODO (nostros): Hacer bool.
    while (this->message_count < 5000) {
        // Search for a connection
        this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

        // Found a connection
        if (this->connection != -1) {
            answer_request();
        }
        sleep(1);
    }

    std::cout << std::endl << "[SERVIDOR_BASE_DATOS DETENIDO]" << std::endl;
}

/*
 * @brief The server answers a request from a client, validating
 * the data of the user in the file system.
*/
void data_server::answer_request() {
    std::cout << "[MENSAJE RECIBIDO] #" << ++this->message_count;

    char strIpRemoto[INET6_ADDRSTRLEN];
    struct sockaddr_in *s = (struct sockaddr_in*)& this->ipRemoto;
    int n = 0;

    inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
    std::cout << " IP Remoto: " << strIpRemoto << std::endl;

    while (this->connection != -1 &&
           (n = read(this->connection, this->data, sizeof(this->data))) > 0) {
        // connection es socket cliente
        std::cout << "Recibi: " << this->data << std::endl;
        if (this->data[0] == '#') {
            close(this->connection);
        } else {
            this->process_data();
        }
    }
}

// TODO(nosotros): documentar
void data_server::see_process_requests() {
    // TODO (nosotros): adaptar
    // Supongamos que llega: define (el que me trajo hasta acá, usuario)
    // TODO(nosotros): sacar sucursal e ir sacando filas
    bool rows_left = true; // this means there still is data to fill.
    int borrar_despues = 0;  // para que pare ahorita que no sacamos nada de la base de datos
    while (rows_left && borrar_despues < 4) {

    }
}

// TODO(us): Document
void data_server::process_data() {
    std::string username = "\0";
    std::string hash = "\0";
    std::cout << "tengo: " << data[0] << " antes de switch  y DELETE_USER es " << (char) DELETE_USER << std::endl;
    switch ((int) data[0]) {
        case CREATE_USER:
            // TODO(luis): hacer
            break;
        case DELETE_USER:
            // TODO(luis): hacer
            std::cout << " Me llego el mensaje \n";
            memset(this->data, '\0', DATA_SIZE);
            this->data[0] = 'h';
            this->data[1] = 'o';
            this->data[2] = 'l';
            this->data[3] = 'a';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;
        case PAYMENT_PROOF:
            // TODO(Cris): hacer
            break;
        case WORK_PROOF:
            // TODO(Cris): hacer
            break;
        case SALARY_PROOF:
            // TODO(Cris): hacer
            break;
        case SALARY_CONSULT:
            // TODO(Luis): hacer
            break;
        case RECORD_CONSULT:
            // TODO(Angie): hacer
            break;
        case SEE_CONSULT_REQUESTS:
            // TODO(Angie): hacer
            break;
        case CONSULT_REQUESTS:
            // TODO(Angie): hacer
            break;
        case SEE_PROCESS_REQUESTS:
            // TODO(todos): hacer
            this->see_process_requests();
            break;
        case PROCESS_REQUESTS:
            // TODO(todos): hacer
            break;
        case VACATION_REQUEST:
            // TODO(Luis): hacer
            break;
        case CONSULT_VACATION:
            // TODO(Luis): hacer
            break;
        case CONSULT_USER_DATA:
            // TODO(Angie): hacer
            break;
        case CHANGE_USER_DATA:
            // TODO(Angie): hacer
            break;
        case ANSWER_PAYMENT_PROOF:
            // TODO(Cris): hacer
            break;
        case ANSWER_WORK_PROOF:
            // TODO(Cris): hacer
            break;
        case ANSWER_SALARY_PROOF:
            // TODO(Cris): hacer
            break;
        case ANSWER_VACATION_REQUEST:
            // TODO(Cris): hacer
            break;
        case USER_OFFICE:
            // TODO(Angie)
            break;
        case ALL_USERS_OFFICE:
            // TODO(Angie)
            break;
        case DATA_USER:
            // TODO(Angie)
            break;
    }
    // TODO: meter a bitácora
}
