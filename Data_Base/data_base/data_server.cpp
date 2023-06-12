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
    this->logger = new log_generator();
    this->logger->set_params("Data_LOG.txt", "Data Server");
    this->load_from_file();
    this->connection = -1;
    this->continue_waiting = true;
    this->message_count = 0;
}

/*
 * @brief Destructor
*/
data_server::~data_server() {
    delete this->base;
}

// TODO(nosotros): documentar
void data_server::adapt_data(char* data, std::string& new_info, int pos) {
    for (int i = 0; i < DATA_SIZE-1; ++i){
        data[i] = new_info[i+pos];
    }
    pos -= 1;
    data[DATA_SIZE-1] = '\0';
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

/*
 * @brief Loads the data base from .txt corresponding to each table
*/
void data_server::load_from_file() {
    this->load_offices();
    this->load_employees();
    this->load_requests();
    this->load_laboral_data();
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
    int shift_available = 0;
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

            // find the shift_available
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the shift_available
            shift_available = stoi(partial_line);

            // find the last_laboral_data
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            this->copy_string(line,partial_line,initial_pos ,end_pos-1);
            // save the last_laboral_data
            last_laboral_data = stoi(partial_line);

            // add to offices table
            this->base->add_employee(user, name, id, phone_number, email, office_id
                    , roles, available_vacations, shift_available, last_laboral_data);
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
            this->base->add_laboral_data(user, start_day, start_month, start_year, end_day
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
    int solved = 0;
    int day_request = 0;
    int month_request = 0;
    int year_request = 0;
    int day_answer = 0;
    int month_answer = 0;
    int year_answer = 0;
    int type = 0;
    std::string vacations = "\0";
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

            // find the vacations content
            initial_pos = end_pos;  // starts after the ','
            this->find_next(line, end_pos);
            // save the vacations
            this->copy_string(line,vacations,initial_pos ,end_pos-1);

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

            this->base->add_request(user, solved, day_request, month_request, year_request, day_answer
                                    , month_answer, year_answer, type, vacations, proof_type
                                    , content_proof, user_signing_boss_proof);

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
            this->base->add_record (user, day, month, year, annotation);
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

    socklen_t l = sizeof(this->ipRemoto);
    std::cout << std::endl << "[SERVIDOR_BASE_DATOS ESCUCHANDO]" << std::endl;

    while (continue_waiting == true) {
        // Search for a connection
        this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

        // Found a connection
        if (this->connection != -1) {
            answer_request();
        }
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
        std::cout << "[SERVIDOR DE DATOS RECIBIE] " << this->data << std::endl;
        if (this->data[0] == '#') {
            close(this->connection);
        } else {
            if (this->data[0] != '&') {
                this->logger->add_to_log(strIpRemoto, "received", this->data);
                this->process_data(strIpRemoto);
            }
        }
    }
}

// TODO(nosotros): documentar
void data_server::see_process_requests(std::string remote_ip) {
    std::string user = "";
    for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
        user += this->data[i];
    }
    read(this->connection, this->data, sizeof(this->data)); // discard &
    int office = this->base->consult_employee_office(user);
    std::string to_send_back = this->base->consult_process_requests_of_office(office);
    // find the size of the package to send
    int total_m = (int) (to_send_back.length() / (DATA_SIZE-1))
                  + (((int)(to_send_back.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m; ++i) {
        adapt_data(data, to_send_back, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::give_role(std::string remote_ip) {
    std::string user = "";
    for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
        user += this->data[i];
    }
    int error = 0;
    read(this->connection, this->data, sizeof(this->data)); // discard &
    char to_send = this->base->get_rol(user, error);
    std::string to_log = "";
    to_log += to_send;
    this->logger->add_answer_log(remote_ip, "sent", to_log);
    memset(this->data, '\0', DATA_SIZE);
    if (error != -1) {
        this->data[0] = '1';
        this->data[1] = to_send;
        write(this->connection, this->data, DATA_SIZE);
    } else {
        this->data[0] = '0';
        write(this->connection, this->data, DATA_SIZE);
    }
}

void data_server::create_user_case(std::string remote_ip) {
    // Obtain information from datagram
    std::string username = "";
    std::string identification = "";
    std::string name = "";
    this->obtain_create_information(username, identification, name);
    // Remove the unnecesary & as only one package is needed
    read(this->connection, this->data, sizeof(this->data));
    // Clear data
    memset(this->data, '\0', DATA_SIZE);
    std::string result = "0";
    // Check if the user exists
    if (!this->base->user_exists(username)) {
        this->base->add_employee(username, name, identification, "-", "-", 0, 32, 0, 0, 0);
        result = "1";
    }
    this->logger->add_to_log(remote_ip, "sent", result);
    data[0] = result[0];
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::vacation_request(std::string remote_ip) {
    std::string result = "";
    std::string receive = "";
    int n = 1;
    while (this->connection != -1 && n > 0 && this->data[0] != '&') {
        std::cout << "[SERVIDOR DATOS RECIBE]  " << this->data << "\n";
        // Copy the packets into receive
        for (int i = 0; i < DATA_SIZE && this->data[i] != '\0'; ++i) {
            receive += this->data[i];
        }
        // Read the next
        n = read(this->connection, this->data, sizeof(this->data));
    }
    // Obtain the username
    std::string username = "";
    int i = 1;
    for (; i < 11 && receive[i] != ','; ++i) {
        username += receive[i];
    }
    // Move from the ,
    ++i;
    // Obtain the vacation part
    std::string vacation = "";
    for (; receive[i] != ','; ++i) {
        vacation += receive[i];
    }
    ++i;
    std::string request_days = "";
    // Obtain the requested days
    for (; receive[i] != '\0'; ++i) {
        request_days += receive[i];
    }
    std::string temporal_vac = this->base->get_available_vacations(username);
    double requested = std::stod(request_days);
    double contained = std::stod(temporal_vac);
    if (requested > contained) {
        // It can't be requested
        result = "0";
    } else {
        // Obtain the current date
        QDate date = QDate::currentDate();
        int day = date.day();
        int month = date.month();
        int year = date.year();
        // Prepare to add to data base
        vacation += "," + request_days;
        this->base->add_request(username, 0, day, month, year, 0, 0, 0, 0, vacation, 0, "\0", "\0");
        result = "1";
    }
    // Send the answer
    memset(this->data, '\0', DATA_SIZE);
    this->data[0] = result[0];
    // Send the answer
    write(this->connection, this->data, DATA_SIZE);
    // Send the &
    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_to_log(remote_ip, "sent", result);
}

void data_server::consult_vacations(std::string remote_ip) {
    std::string to_send = "";
    std::string username = "";
    std::string name = "";
    std::string identification = "";
    std::string vacations = "";
    // Obtain the username
    for (int i = 1; i < 10 && this->data[i] != ','; ++i) {
        username += this->data[i];
    }
    // Obtain the name from the database
    name = this->base->get_name(username);
    // Obtain the identification from the database
    identification = this->base->get_id(username);
    // Obtain the vacations from the database
    vacations = this->base->get_available_vacations(username);
    to_send += name + "," + identification + "," + vacations + ",";
    this->logger->add_answer_log(remote_ip, "sent", to_send);
    // Adapt the data to send it
    this->adapt_data(this->data, to_send, 0);
    // Send the answer
    write(this->connection, this->data, DATA_SIZE);
    // Send the &
    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::obtain_create_information(std::string& username, std::string& identification, std::string& name) {
    // Obtain the other username
    // Used to store the position of the first comma
    int i = 2;
    for (; this->data[i] != ','; ++i) {
        // Ignore the username of the request
    }
    // Increase one more to avoid the comma
    ++i;
    for (; this->data[i] != ','; ++i) {
        username += this->data[i];
    }
    // Increase one more to avoid the comma
    ++i;
    for (; this->data[i] != ','; ++i) {
        identification += this->data[i];
    }
    ++i;
    for (; this->data[i] != ','; ++i) {
        name += this->data[i];
    }
}

void data_server::delete_user_case(std::string remote_ip) {
    std::string username = "";
    // Obtain the username from data
    for (int i = 2; i < DATA_SIZE && this->data[i] != ','; ++i) {
        username += this->data[i];
    }
    // Remove the unnecesary & as only one package is needed
    read(this->connection, this->data, sizeof(this->data));
    // Clear data
    memset(this->data, '\0', DATA_SIZE);
    std::string result = "0";
    // Check if the user exists
    if (this->base->user_exists(username)) {

        this->base->delete_user(username);

        result = "1";
    }
    this->logger->add_answer_log(remote_ip, "sent", result);
    data[0] = result[0];
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::consult_salary_case(std::string remote_ip) {
    security security_manager;
    std::string user = "";
    for (int i = 1; i < DATA_SIZE && data[i] != ','; i++){
        user += data[i];
    }
    read(this->connection, this->data, sizeof(this->data));
    memset(this->data, '\0', DATA_SIZE);

    int gross_salary = this->base->get_salary(user);
    int deductibles = this->base->get_deductibles(user);
    std::string name = this->base->get_name(user);
    std::string id = this->base->get_id(user);
    int salary = gross_salary - deductibles;
    std::string buffer = security_manager.encrypt(std::to_string(gross_salary));

    std::string gross_salary_ascii = "";
    size_t i = 0;
    for (i = 0; i < buffer.length(); ++i) {
        gross_salary_ascii += std::to_string((int)buffer[i]);
        gross_salary_ascii += ",";
    }
    // gross_salary_ascii += '\0';

    buffer = security_manager.encrypt(std::to_string(salary));

    std::string net_salary_ascii = "";
    for (i = 0; i < buffer.length(); ++i) {
        net_salary_ascii += std::to_string((int)buffer[i]);
        net_salary_ascii += ",";
    }
    // net_salary_ascii += '\0';

    std::string to_send = " ";
    to_send += name + ";";
    to_send += id + ";";
    to_send += gross_salary_ascii + ";";
    to_send += net_salary_ascii + ";";

    adapt_data(this->data, to_send, 0);
    this->logger->add_answer_log(remote_ip, "sent", to_send);
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::proof_case(std::string remote_ip, std::string description) {
    int type = (int)data[0] - 71;

    std::string user = "";
    std::string day = "";
    std::string month = "";
    std::string year = "";
    int i = 0;
    int j = 0;
    for (i = 1; i < DATA_SIZE && data[i] != ','; i++){
        user += data[i];
    }

    for (j = i+1; j < DATA_SIZE && data[j] != ','; j++) {
        day += data[j];
    }

    for (i = j+1; i < DATA_SIZE && data[i] != ','; i++) {
        month += data[i];
    }

    for (j = i+1; j < DATA_SIZE && data[j] != ','; j++) {
        year += data[j];
    }

    // Remove the unnecesary & as only one package is needed
    read(this->connection, this->data, sizeof(this->data));
    // Clear data
    memset(this->data, '\0', DATA_SIZE);
    std::string result = "1";
    this->base->add_request(user, 0, stoi(day), stoi(month), stoi(year), 0, 0, 0, 1, "", type, description,"");
    this->logger->add_answer_log(remote_ip, "sent", result);
    data[0] = ' ';
    data[1] = '1';
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(us): Document
void data_server::process_data(std::string remote_ip) {
    std::string to_send = " ";
    std::string user = "";

    /*
      * Nota: cada vez que haga un write (sin contar & y #) hay que meterlo en el log.
      * Hay dos tipos de agregados a log:
      *
      * this->logger->add_answer_log(params)
      * this->loger->add_to_log(params)
      *
      * Los dos métodos reciben las mismas 3 cositas/parametros:
      *
      * 1. ip (que es el remote_ip que recibe este método como parámetro)
      * 2. send_or_receive (que indica un mini mensaje del inicio para ver si la info es mandada o recibida, lit es ponerle "sent" o "received" y así sale en el log)
      * 3. to_send (que es lo que se acaba de mandar, aka. this->data)
      *
      * La diferencia entre ambos métodos es que add_to_log recibe en data[0] el id del pedido
      * y muestra si es CREATE_USER, DELETE_USER, etc. El add_answer_log no hace ese procesamiento
      * de data[0], simplemente pega el to_sent así como viene (cosa que sirve cuando es una respuesta
      * o no es el primer paquete que se está enviando o recibiendo)
    */

    switch ((int) data[0]) {
        case CREATE_USER:
            this->create_user_case(remote_ip);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case DELETE_USER:
            this->delete_user_case(remote_ip);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case PAYMENT_PROOF:
            this->proof_case(remote_ip, "Solicitud de constancia de pago");
            memset(this->data, '\0', DATA_SIZE);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case WORK_PROOF:
            this->proof_case(remote_ip, "Solicitud de constancia laboral");
            memset(this->data, '\0', DATA_SIZE);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case SALARY_PROOF:
            this->proof_case(remote_ip, "Solicitud de constancia salarial");
            memset(this->data, '\0', DATA_SIZE);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case SALARY_CONSULT:
            this->consult_salary_case(remote_ip);
            memset(this->data, '\0', DATA_SIZE);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case RECORD_CONSULT:
            this->consult_record(remote_ip);
            break;

        case SEE_CONSULT_REQUESTS:
            this->see_consult_requests(remote_ip);
            break;

        case CONSULT_REQUESTS:
            this->consult_request(remote_ip);
            break;

        case SEE_PROCESS_REQUESTS:
            this->see_process_requests(remote_ip);
            break;

        case PROCESS_REQUESTS:
            this->process_requests(remote_ip);
            break;

        case VACATION_REQUEST:
            this->vacation_request(remote_ip);
            break;

        case CONSULT_VACATION:
            this->consult_vacations(remote_ip);
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
            this->get_user_office(remote_ip);
            break;

        case ALL_USERS_OFFICE:
            this->get_all_users_from_office(remote_ip);
            break;

        case DATA_USER:
            this->get_data_user(remote_ip);
            break;

        case CHANGE_PHONE:
            this->change_phone(remote_ip);
            break;

        case CHANGE_EMAIL:
            this->change_email(remote_ip);
            break;

        case CHANGE_OFFICE_ID:
            this->change_office(remote_ip);
            break;

        case CHANGE_ROLES:
            this->change_roles(remote_ip);
            break;

        case CHANGE_VACATIONS:
            this->change_vacations(remote_ip);
            break;

        case CHANGE_LABORAL_DATA:
            this->change_laboral_data(remote_ip);
            break;

        case CHANGE_SHIFT:
            this->change_shift(remote_ip);
            break;

        case GET_ROLES:
            this->give_role(remote_ip);
            this->data[0] = '&';
            std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case ADD_RECORD:
            this->add_record(remote_ip);
            break;
    }
}

// TODO(nosotros): documentar
void data_server::get_user_office(std::string remote_ip) {
    std::string to_send = "\0";
    int to_send_int = 0;
    int i = 1;  // data[0] is USER_OFFICE

    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    to_send_int = this->base->consult_employee_office(to_send);
    to_send = std::to_string(to_send_int);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::get_all_users_from_office(std::string remote_ip) {
    std::string to_send = "\0";
    int i = 1;  // data[0] is USER_OFFICE

    // when a ',' is found, the message to be sent is finished, what remains is the user who is modifying
    while (data[i] != '\0') {
        to_send += data[i++];
    }

    // ask the data base for the result
    to_send = this->base->consult_employees_of_an_office(stoi(to_send));

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::get_data_user(std::string remote_ip) {
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is USER_OFFICE
    while (data[i] != '\0') {
        to_send += data[i++];
    }
    to_send += "\0";

    // ask the data base for the result
    to_send = this->base->consult_employee_data(to_send);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_phone(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_PHONE
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the phone_number will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    if (this->base->change_phone(user, to_send)) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_email(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_EMAIL
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the email will be read
    ++i;
    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    if (this->base->change_email(user, to_send)) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_vacations(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_VACATIONS
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the vacations will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int to_send_int = stoi(to_send);

    // ask the data base for the result
    if (this->base->change_vacations(user, to_send_int)) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_shift(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_SHIFT
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the shift will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int to_send_int = stoi(to_send);

    // ask the data base for the result
    if (this->base->change_shift(user, to_send_int)) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_laboral_data(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";
    std::string job_title = "\0";

    // save the data in the corresponding variables
    // find the user
    int i = 1;  // data[0] is CHANGE_LABORAL_DATA
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the day will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int day = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the month will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int month = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the year will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int year = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the job_title will be read
    ++i;
    while (this->data[i] != ',') {
        job_title += this->data[i++];
    }
    // the ',' was found, now the salary will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int salary = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the deductibles will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int deductibles = stoi(to_send);


    // change the last laboral data's end date
    if (this->base->set_end_date_laboral_data(user, day, month, year)) {
        // add the new laboral data
        int to_send_int = this->base->add_laboral_data(user, day, month, year, 0, 0, 0, salary, deductibles, job_title);
            if (to_send_int != -1) {
                // save the new laboral data in the user
                if (this->base->change_last_laboral_data(user, to_send_int)) {
                memset(this->data, '1', DATA_SIZE);
                }
        } else {
                memset(this->data, '0', DATA_SIZE);
        }
    } else {
        memset(this->data, '0', DATA_SIZE);
    }

    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_office(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_OFFICE_ID
    while (data[i] != ',') {
        user += data[i++];
    }
    // the ',' was found, now the office will be read
    to_send = data[++i];
    int to_send_int = stoi(to_send);

    // ask the data base for the result
    if (this->base->change_office(user, to_send_int)) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::change_roles(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // find the user
    int i = 1;  // data[0] is CHANGE_ROLES
    while (data[i] != ',') {
        user += data[i++];
    }
    // the ',' was found, now the roles will be read
    to_send = data[++i];

    // ask the data base for the result
    if (this->base->change_roles(user, to_send[0])) {  // success
        memset(this->data, '1', DATA_SIZE);
    } else {  // the change was not possible
        memset(this->data, '0', DATA_SIZE);
    }
    write(this->connection, data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::add_record(std::string remote_ip) {
    std::string user = "\0";
    std::string to_send = "\0";

    // save the data in the corresponding variables
    // find the user
    int i = 1;  // data[0] is ADD_RECORD
    while (this->data[i] != ',') {
        user += this->data[i++];
    }
    // the ',' was found, now the day will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int day = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the month will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int month = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the year will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    int year = stoi(to_send);
    to_send = "\0";
    // the ',' was found, now the record will be read
    ++i;
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    this->base->add_record(user, day, month, year, to_send);
    memset(this->data, '1', DATA_SIZE);
    write(this->connection, this->data, DATA_SIZE);
    this->logger->add_answer_log(remote_ip, "sent", this->data);

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::consult_record(std::string remote_ip) {
    std::string to_send = "\0";
    int i = 1;  // data[0] is USER_OFFICE

    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    to_send = this->base->consult_records(to_send);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1))+ (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO]: " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(nosotros): documentar
void data_server::see_consult_requests(std::string remote_ip) {
    std::string to_send = "\0";
    int i = 1;

    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }

    // ask the data base for the result
    to_send = this->base->consult_requests(to_send);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO]: " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::consult_request(std::string remote_ip) {
    std::string to_send = "\0";
    int id = 0;
    int type = 0;
    int i = 1;

    // find the id
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    id = stoi(to_send);
    to_send = "\0";
    ++i;

    // find the type
    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }
    type = stoi(to_send);

    // ask the data base for the result
    to_send = this->base->consult_request(id, type);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO]: " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::process_requests(std::string remote_ip) {
    std::string to_send = "\0";
    int i = 1;
    int id = 0;
    int solved = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    std::string signing_boss = "\0";

    // find the data
    // find the signing boss
    while (this->data[i] != ',') {
        signing_boss += this->data[i++];
    }
    ++i;

    // find the id
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    id = stoi(to_send);
    to_send = "\0";
    ++i;

    // find if solved
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    solved = stoi(to_send);
    to_send = "\0";
    ++i;

    // find the day
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    day = stoi(to_send);
    to_send = "\0";
    ++i;

    // find the month
    while (this->data[i] != ',') {
        to_send += this->data[i++];
    }
    month = stoi(to_send);
    to_send = "\0";
    ++i;

    // find the year
    while (this->data[i] != '\0') {
        to_send += this->data[i++];
    }
    year = stoi(to_send);

    // ask the data base for the answer
    to_send = (this->base->change_request_solved(id, solved, day, month, year, signing_boss) ? 1 : 0);

    // find the size of the package to send
    int total_m = (int) (to_send.length() / (DATA_SIZE-1)) + (((int)(to_send.length() % (DATA_SIZE-1)) > 0) ? 1 : 0);

    // send the data
    for (int i = 0; i < total_m && i < 10; ++i) {
        adapt_data(data, to_send, DATA_SIZE * i);
        std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO]: " << data << std::endl;
        write(this->connection, data, DATA_SIZE);
        this->logger->add_answer_log(remote_ip, "sent", this->data);
    }

    this->data[0] = '&';
    std::cout << "[SERVIDOR DATOS -> INTERMEDIARIO] " << this->data << "\n";
    write(this->connection, this->data, DATA_SIZE);
}
