#include "client.h"
#include <QMessageBox>

/**
 * @brief Construct a new client::client object
 */
client::client() {
    this->decrypter = new common();
    this->logger = new log_generator("../interface_LOG.txt", "Client Log File");
    std::string encrypted;
    std::string temp;
    // Read the setup files
    std::ifstream config_file("../client.config");
    if (config_file.is_open()) {
        getline(config_file, encrypted);
        this->decrypter->decrypt(encrypted, this->intermediary_ip);
        getline(config_file, encrypted);
        this->decrypter->decrypt(encrypted, temp);
        this->port = std::stoi(temp);
        config_file.close();
    } else {
        qDebug() << "ERROR: config file no existente";
    }
}

/**
 * @brief Default destructor
 */
client::~client() {
    delete this->decrypter;
}

/**
 * @brief Inserts a new string into data starting at received position
 *
 * @param data Array of data into which the new info shall be placed
 * @param new_info Information that will be placed into data
 * @param pos Position to start the transfer
 */
void client::adapt_data(char* data, std::string& new_info, int pos) {
    for (int i = 0; i < CLIENT_DATA_SIZE-1; ++i){
        data[i] = new_info[i+pos];
    }
    data[CLIENT_DATA_SIZE-1] = '\0';
}

/**
 * @brief Sends and receives information to intermediary
 *
 * @param to_send Information that needs to be sent
 * @return std::string Information received
 */
std::string client::send_and_receive(std::string to_send) {
    std::string result = "";
    int s = 0, n = 0; // s:socket  n: counter
    // Used to write what is read
    char* data = new char[CLIENT_DATA_SIZE];
    struct sockaddr_in ipServidor;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Error de creación de socket" << std::endl;
    } else {
        ipServidor.sin_family = AF_INET;
        ipServidor.sin_port = htons(this->port);
        ipServidor.sin_addr.s_addr = inet_addr(this->intermediary_ip.data());
        // Attempt to connect to the server
        if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
            std::cout << std::endl << "Error de conexión por IP o puerto" << std::endl;
            QMessageBox show_error =  QMessageBox();
            show_error.setWindowTitle("Error");
            show_error.setModal(true);
            show_error.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_error.setText("Error de conexión por IP o puerto. Favor contactar al encargado");
                show_error.exec();
        } else {
            // Set the data to \0
            memset(data, '\0', CLIENT_DATA_SIZE);
            int total_m = (int) (to_send.length() / (CLIENT_DATA_SIZE-1))
                          + (((int)(to_send.length() % (CLIENT_DATA_SIZE-1)) > 0) ? 1 : 0);
            for (int i = 0; i < total_m; ++i) {
                adapt_data(data, to_send, CLIENT_DATA_SIZE * i);
                std::cout << "[CLIENTE RECIBE] " << data << std::endl;
                write(s, data, CLIENT_DATA_SIZE);
                if (i == 0) {
                    this->logger->add_to_log("AUDITOR", "TO_SERVER", data);
                } else {
                    this->logger->add_answer_log("AUDITOR", "TO_SERVER", data);
                }
            }
            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "&";
            adapt_data(data, to_send, 0);
            std::cout << "[CLIENTE ENVIA] " << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);
            data[0] = '0';
            while (((n = read(s, data, CLIENT_DATA_SIZE)) > 0) && (data[0] != '&')) {
                // Check for an error
                if (this->server_error(data)) {
                    break;
                }
                result += data;
                std::cout << "[CLIENTE RECIBE] " << data << std::endl;
                this->logger->add_answer_log("AUDITOR", "FROM_SERVER", data);
            }
            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "#";
            adapt_data(data, to_send, 0);
            std::cout << "[CLIENTE ENVIA]" << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);
            // Could not read
            if (n < 0) {
                std::cout << std::endl << "Error de lectura" << std::endl;
            }
        }
    }
    delete [] data;
    return result;
}

bool client::server_error(char* data) {
    bool answer = false;
    std::string data_string = data;
    if (data_string == "LOGIN_SERVER_ERROR") {
        answer = true;
        this->show_error("Error de fallo de conexión con servidor de sistema de archivos");
    } else if (data_string == "DATA_SERVER_ERROR") {
        answer = true;
        this->show_error("Error de fallo de conexión con servidor de base de de datos");
    }
    return answer;
}

void client::show_error(std::string error) {
    QMessageBox error_message;
    error_message.setText(QString::fromStdString(error));
    error_message.setWindowTitle("Error");
    error_message.setModal(true);
    error_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    error_message.exec();
}

void client::show_success(std::string success) {
    QMessageBox success_box;
    success_box.setText(QString::fromStdString(success));
    success_box.setWindowTitle("Información");
    success_box.setModal(true);
    success_box.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    success_box.exec();
}
