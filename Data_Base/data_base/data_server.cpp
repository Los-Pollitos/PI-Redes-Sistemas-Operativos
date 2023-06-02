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
    std::cout << base.consult_office_name(1);
}

/*
 * @brief Destructor
*/
data_server::~data_server() {
    delete this->base;
}

/*
 * @brief Loads the file system from a .txt file containing the necessary
 * login information, creating the image of the file system for future uses.
*/
void data_server::load_from_file() {

}

/*
 * @brief The server waits for a request from a client to answer it.
 */
void data_server::wait_for_request() {
    int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in ip;

    memset(&ip, '0', sizeof(ip));
    memset(this->data, '0', sizeof(this->data));
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = htonl(INADDR_ANY);
    ip.sin_port = htons(8081);

    bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
    listen(socketServidor, 20);

    sleep(1);
    socklen_t l = sizeof(this->ipRemoto);
    char strIpRemoto[INET6_ADDRSTRLEN];
    int port;
    std::cout << std::endl << "[SERVIDOR ESCUCHANDO]" << std::endl;
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

// TODOD (us): Document
void data_server::process_data() {
    std::string username = "\0";
    std::string hash = "\0";
    // TODO (stoi)
    switch (data[0]) {
        case CREATE_USER:
            // TODO(luis): hacer
            break;
        case DELETE_USER:
            // TODO(luis): hacer
            break;
        case PAYMENT_PROOF:

            break;
        case WORK_PROOF:

            break;
        case SALARY_PROOF:

            break;
        case SALARY_CONSULT:

            break;
        case RECORD_CONSULT:

            break;
        case CONSULT_REQUESTS:

            break;
        case VACATION_REQUEST:

            break;
        case CONSULT_VACATION:

            break;
        case CONSULT_USER_DATA:

            break;
        case CHANGE_USER_DATA:

            break;
        case ANSWER_PAYMENT_PROOF:

            break;
        case ANSWER_WORK_PROOF:

            break;
        case ANSWER_SALARY_PROOF:

            break;
        case ANSWER_VACATION_REQUEST:

            break;
    }
    // TODO: meter a bitácora
}
