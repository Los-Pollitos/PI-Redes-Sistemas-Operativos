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

            this->base->add_request(user, solved, day_request, month_request, year_request, day_answer
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
            if (this->data[0] != '&') {
                this->logger->add_to_log(strIpRemoto, "received", this->data);
            }
            this->process_data(strIpRemoto);
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

void data_server::give_role(std::string remote_ip) {
    std::string user = "";
    for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
        user += this->data[i];
    }
    read(this->connection, this->data, sizeof(this->data)); // discard &
    char to_send = this->base->get_rol(user);
    std::string to_log = "";
    to_log += to_send;
    this->logger->add_answer_log(remote_ip, "sent", to_log);
    memset(this->data, '\0', DATA_SIZE);
    this->data[0] = '0';
    this->data[1] = to_send;
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::create_user_case(std::string remote_ip) {
    std::string username = "";
    // Obtain the username from data
    for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
        username += this->data[i];
    }
    // Remove the unnecesary & as only one package is needed
    read(this->connection, this->data, sizeof(this->data));
    // Clear data
    memset(this->data, '\0', DATA_SIZE);
    std::string result = "0";
    // Check if the user exists
    if (this->base->user_exists(username)) {
        // d_gmora,Gerardo Mora Ortiz,-,-,-,0,1,0,0
        this->base->add_employee(username, "-", "-", "-", "-",0,1,0,0);
        result = "1";
    }
    this->logger->add_answer_log(remote_ip, "sent", result);
    data[0] = result[0];
    write(this->connection, this->data, DATA_SIZE);
}

void data_server::delete_user_case(std::string remote_ip) {
    std::string username = "";
    // Obtain the username from data
    for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
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
    }
    this->logger->add_answer_log(remote_ip, "sent", result);
    data[0] = result[0];
    write(this->connection, this->data, DATA_SIZE);
}

// TODO(us): Document
void data_server::process_data(std::string remote_ip) {
    std::string to_send = " ";
    std::string user = "";
    int total_m = 0;
    int i = 0;
    int to_send_int = 0;

    std::string job_title = "\0";
    int day = 0;
    int month = 0;
    int year = 0;
    int salary = 0;
    int deductibles = 0;

    // TODO(nosotros): borrar
//    std::cout << "tengo: " << data[0] << " antes de switch  y DELETE_USER es " << (char) DELETE_USER << std::endl;

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
            // TODO(luis): hacer
            this->create_user_case(remote_ip);
            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;
        case DELETE_USER:
            // TODO(luis): hacer
            this->delete_user_case(remote_ip);
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
            for (int i = 1; i < DATA_SIZE || data[i] == '\0'; i++){
                user += data[i];
            }
            std::cout << this->base->get_salary(user) << std::endl;
            memset(this->data, '\0', DATA_SIZE);
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
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is USER_OFFICE

            // TODO(Angie): borrar
            std::cout << "data[" << i << "] = " << data[i] << std::endl;

            while (data[i] != '\0') {

                // TODO(Angie): borrar
                std::cout << "data[" << i << "] = " << data[i] << std::endl;

                to_send += data[i++];
            }

            // ask the data base for the result
            to_send_int = this->base->consult_employee_office(to_send);
            to_send = std::to_string(to_send_int);

            // find the size of the package to send
            total_m = (int) (to_send.length() / DATA_SIZE)
                          + (((int)(to_send.length() % DATA_SIZE) > 0) ? 1 : 0);

            // send the data
            for (int i = 0; i < total_m && i < 10; ++i) {
                adapt_data(data, to_send, DATA_SIZE * i);
                std::cout << "Voy a mandar: " << data << std::endl;
                write(this->connection, data, DATA_SIZE);
                this->logger->add_answer_log(remote_ip, "sent", this->data);
            }

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case ALL_USERS_OFFICE:
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is USER_OFFICE
            while (data[i] != '\0') {
                to_send += data[i++];
            }

            // ask the data base for the result
            to_send = this->base->consult_employees_of_an_office(stoi(to_send));

            // find the size of the package to send
            total_m = (int) (to_send.length() / DATA_SIZE)
                      + (((int)(to_send.length() % DATA_SIZE) > 0) ? 1 : 0);

            // send the data
            for (int i = 0; i < total_m; ++i) {
                adapt_data(data, to_send, DATA_SIZE * i);
                std::cout << "Voy a mandar: " << data << std::endl;
                write(this->connection, data, DATA_SIZE);
                this->logger->add_answer_log(remote_ip, "sent", this->data);
            }

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case DATA_USER:
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is USER_OFFICE
            while (data[i] != '\0') {
                to_send += data[i++];
            }

            // ask the data base for the result
            to_send = this->base->consult_employee_data(to_send);

            // find the size of the package to send
            total_m = (int) (to_send.length() / DATA_SIZE)
                      + (((int)(to_send.length() % DATA_SIZE) > 0) ? 1 : 0);

            // send the data
            for (int i = 0; i < total_m && i < 10; ++i) {
                adapt_data(data, to_send, DATA_SIZE * i);
                std::cout << "Voy a mandar: " << data << std::endl;
                write(this->connection, data, DATA_SIZE);
                this->logger->add_answer_log(remote_ip, "sent", this->data);
            }

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_PHONE:
            user = "\0";
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is CHANGE_PHONE
            while (data[i] != ',') {
                user += data[i++];
            }
            // the ',' was found, now the phone_number will be read
            ++i;
            while (data[i] != '\0') {
                to_send += data[i++];
            }

            // ask the data base for the result
            if (this->base->change_phone(user, to_send)) {  // success
                memset(this->data, '1', DATA_SIZE);
            } else {  // the change was not possible
                memset(this->data, '0', DATA_SIZE);
            }
            write(this->connection, data, DATA_SIZE);
            this->logger->add_answer_log(remote_ip, "sent", this->data);

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_EMAIL:
            user = "\0";
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is CHANGE_EMAIL
            while (data[i] != ',') {
                user += data[i++];
            }
            // the ',' was found, now the email will be read
            ++i;
            while (data[i] != '\0') {
                to_send += data[i++];
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
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_OFFICE_ID:
            user = "\0";
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is CHANGE_OFFICE_ID
            while (data[i] != ',') {
                user += data[i++];
            }
            // the ',' was found, now the office will be read
            to_send = data[++i];
            to_send_int = to_send[0];

            // ask the data base for the result
            if (this->base->change_office(user, to_send_int)) {  // success
                memset(this->data, '1', DATA_SIZE);
            } else {  // the change was not possible
                memset(this->data, '0', DATA_SIZE);
            }
            write(this->connection, data, DATA_SIZE);
            this->logger->add_answer_log(remote_ip, "sent", this->data);

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_ROLES:
            user = "\0";
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is CHANGE_ROLES
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
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_VACATIONS:
            user = "\0";
            to_send = "\0";

            // find the user
            i = 1;  // data[0] is CHANGE_VACATIONS
            while (data[i] != ',') {
                user += data[i++];
            }
            // the ',' was found, now the vacations will be read
            ++i;
            while (data[i] != '\0') {
                to_send += data[i++];
            }
            to_send_int = stoi(to_send);

            // ask the data base for the result
            if (this->base->change_vacations(user, to_send_int)) {  // success
                memset(this->data, '1', DATA_SIZE);
            } else {  // the change was not possible
                memset(this->data, '0', DATA_SIZE);
            }
            write(this->connection, data, DATA_SIZE);
            this->logger->add_answer_log(remote_ip, "sent", this->data);

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case CHANGE_LABORAL_DATA:
            user = "\0";
            to_send = "\0";

            // save the data in the corresponding variables
            // find the user
            i = 1;  // data[0] is CHANGE_LABORAL_DATA
            while (data[i] != ',') {
                user += data[i];
            }
            // the ',' was found, now the day will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            day = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the month will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            month = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the year will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            year = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the job_title will be read
            ++i;
            while (data[i] != ',') {
                job_title += data[i];
            }
            // the ',' was found, now the salary will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            salary = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the deductibles will be read
            ++i;
            while (data[i] != '\0') {
                to_send += data[i];
            }
            deductibles = stoi(to_send);


            // change the last laboral data's end date
            if (this->base->set_end_date_laboral_data(user, day, month, year)) {
                // add the new laboral data
                to_send_int = this->base->add_laboral_data(user, day, month, year, 0, 0, 0, salary, deductibles, job_title);
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

            write(this->connection, data, DATA_SIZE);
            this->logger->add_answer_log(remote_ip, "sent", this->data);

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case GET_ROLES:
            this->give_role(remote_ip);
            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;

        case ADD_RECORD:
            user = "\0";
            to_send = "\0";

            // save the data in the corresponding variables
            // find the user
            i = 1;  // data[0] is ADD_RECORD
            while (data[i] != ',') {
                user += data[i];
            }
            // the ',' was found, now the day will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            day = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the month will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            month = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the year will be read
            ++i;
            while (data[i] != ',') {
                to_send += data[i];
            }
            year = stoi(to_send);
            to_send = "\0";
            // the ',' was found, now the record will be read
            ++i;
            while (data[i] != '\0') {
                to_send += data[i];
            }

            // ask the data base for the result
            this->base->add_record(user, day, month, year, to_send);
            memset(this->data, '1', DATA_SIZE);
            write(this->connection, data, DATA_SIZE);
            this->logger->add_answer_log(remote_ip, "sent", this->data);

            this->data[0] = '&';
            std::cout << " Voy a mandar " << this->data << "\n";
            write(this->connection, this->data, DATA_SIZE);
            break;
    }
}
