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

    // TODO(nosotros): borrar
    std::cout << "voy a load from file\n";

    this->load_from_file();
    this->connection = -1;
    this->message_count = 0;

    // TODO (us): borrar
    base->consult_office_name(1);
    base->consult_office_name(2);
    base->consult_office_name(3);
    base->consult_office_name(4);
    base->consult_office_name(5);
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

    // TODO(nosotros): borrar
    std::cout << "despues de copiar string: " << new_line << std::endl;
}

// TODO(nosotros): actualizar documentación
/*
 * @brief Loads the file system from a .txt file containing the necessary
 * login information, creating the image of the file system for future uses.
*/
void data_server::load_from_file() {
    this->load_offices();
//    this->load_employees();
//    this->load_laboral_data();
//    this->load_requests();
//    this->load_records();
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

            // TODO(us): borrar
            std::cout << "lei: " << line << "\n";

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
    char roles = 0;
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
            this->copy_string(line,user,initial_pos,end_pos);

            // find the name
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the name
            this->copy_string(line,name,initial_pos,end_pos);

            // find the id
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the id
            this->copy_string(line,id,initial_pos,end_pos);

            // find the phone number
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the phone number
            this->copy_string(line,phone_number,initial_pos,end_pos);

            // find the email
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the email
            this->copy_string(line,email,initial_pos,end_pos);

            // find the office_id
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the office_id
            office_id = stoi(partial_line);

            // find the roles
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            end_pos += 1;  // roles are a single char always
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the roles
            roles = partial_line[0];

            // find the available_vacations
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the available_vacations
            available_vacations = stoi(partial_line);

            // find the last_laboral_data
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
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
            this->copy_string(line,user,initial_pos,end_pos);

            // find the data_id
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the data_id
            data_id = stoi(partial_line);

            // find the start_day
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the start_day
            start_day = stoi(partial_line);

            // find the start_month
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the start_month
            start_month = stoi(partial_line);

            // find the start_year
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the start_year
            start_year = stoi(partial_line);

            // find the end_day
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the end_day
            end_day = stoi(partial_line);

            // find the end_month
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the end_month
            end_month = stoi(partial_line);

            // find the end_year
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the end_year
            end_year = stoi(partial_line);

            // find the gross_salary
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the gross_salary
            gross_salary = stoi(partial_line);

            // find the deductibles
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the deductibles
            deductibles = stoi(partial_line);

            // find the job_title
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the job_title
            this->copy_string(line,job_title,initial_pos,end_pos);

            // add to laboral data table
            this->base->add_laboral_data(user, data_id , start_day, start_month, start_year, end_day
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
            this->copy_string(line,user,initial_pos,end_pos);

            // find the id
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the id
            id = stoi(partial_line);

            // find if solved
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            end_pos += 1;  // roles are a single int always
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save if solved
            solved = stoi(partial_line);

            // find the day_request
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the day_request
            day_request = stoi(partial_line);

            // find the month_request
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the month_request
            month_request = stoi(partial_line);

            // find the year_request
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the year_request
            year_request = stoi(partial_line);

            // find the day_answer
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the day_answer
            day_answer = stoi(partial_line);

            // find the month_answer
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the month_answer
            month_answer = stoi(partial_line);

            // find the year_answer
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the year_answer
            year_answer = stoi(partial_line);

            // find the type
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the type
            type = stoi(partial_line);

            // find the request_id_vac
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the request_id_vac
            request_id_vac = stoi(partial_line);

            // find the day_vac
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the day_vac
            day_vac = stoi(partial_line);

            // find the month_vac
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the month_vac
            month_vac = stoi(partial_line);

            // find the year_vac
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the year_vac
            year_vac = stoi(partial_line);

            // find the shift_vac
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the shift_vac
            shift_vac = stoi(partial_line);

            // find the proof_type
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the proof_type
            proof_type = stoi(partial_line);

            // find the content_proof
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the content_proof
            this->copy_string(line,content_proof,initial_pos,end_pos);

            // find the user_signing_boss_proof
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the user_signing_boss_proof
            this->copy_string(line,user_signing_boss_proof,initial_pos,end_pos);

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
    std::string boss_user = "\0";
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
            this->copy_string(line,user,initial_pos,end_pos);

            // find the id
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the id
            id = stoi(partial_line);

            // find the boss_user
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the boss_user
            this->copy_string(line,boss_user,initial_pos,end_pos);

            // find the day
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the day
            day = stoi(partial_line);

            // find the month
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the month
            month = stoi(partial_line);

            // find the year
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            this->copy_string(line,partial_line,initial_pos,end_pos);
            // save the year
            year = stoi(partial_line);

            // find the annotation
            end_pos += 2;  // skips the ','
            initial_pos = end_pos;  // starts after the ','
            // save the annotation
            this->copy_string(line,annotation,initial_pos,end_pos);

            // add to records table
            this->base->add_record (user, id, boss_user, day, month, year, annotation);
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
    }
    // TODO: meter a bitácora
}
