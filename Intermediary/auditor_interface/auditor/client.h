#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <ctime>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <QMessageBox>

#include "common.h"
#include "log_generator.h"


#define CLIENT_DATA_SIZE 256


class client {
public:
    client();
    ~client();
    std::string send_and_receive(std::string to_send);
private:
    // Methods
    bool server_error(char* data);
    void adapt_data(char* data, std::string& new_info, int pos);
    void show_error(std::string error);
    void show_success(std::string success);

    // Attributes
    log_generator * logger;
    std::string intermediary_ip;
    int port;
    common* decrypter;
};

#endif // CLIENT_H
