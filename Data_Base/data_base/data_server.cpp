/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "data_server.h"
#include <iostream>

/*
 * @brief Default constructor
*/
data_server::data_server() {
    // Create the data_base
    this->base = new data_base();
    this->connection = -1;
    this->message_count = 0;

    // TODO (us): borrar
    base->add_office(1,"San Jose");
    std::cout << base -> consult_office_name(1);
}

/*
 * @brief Destructor
*/
data_server::~data_server() {
    delete this->base;
}

// TODO(nosotros): documentar
void data_server::adapt_data(char* data, std::string& new_info, int pos) {
    for (int i = 0; i < CLIENT_DATA_SIZE; ++i){
        data[i] = new_info[i+pos];
    }
}

/*
 * @brief Loads the file system from a .txt file containing the necessary
 * login information, creating the image of the file system for future uses.
*/
void data_server::load_from_file() {
    // TODO(nosotros): cargar del archivo
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
    ip.sin_port = htons(1024);

    bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
    listen(socketServidor, 20);

    sleep(1);
    socklen_t l = sizeof(this->ipRemoto);
    std::cout << std::endl << "[SERVIDOR ESCUCHANDO]" << std::endl;
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

    std::cout << std::endl << "[SERVIDOR DETENIDO]" << std::endl;
}

/*
 * @brief The server answers a request from a client, validating
 * the data of the user in the file system.
*/
void data_server::answer_request() {
    std::cout << "[MENSAJE RECIBIDO] #" << ++this->message_count;

    char strIpRemoto[INET6_ADDRSTRLEN];
    struct sockaddr_in *s = (struct sockaddr_in*)& this->ipRemoto;
    int port = ntohs(s->sin_port);
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
    switch (data[0]) {
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
            write(this->connection, this->data, CLIENT_DATA_SIZE);
            this->data[0] = '&';
            write(this->connection, this->data, CLIENT_DATA_SIZE);
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
