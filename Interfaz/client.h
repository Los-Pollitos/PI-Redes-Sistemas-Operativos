#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <ctime>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "log_generator.h"


#define CLIENT_DATA_SIZE 256


class client {
public:
    client();
    std::string send_and_receive(std::string to_send);
private:
    log_generator * logger;
    void adapt_data(char* data, std::string& new_info, int pos);
    std::string intermediary_ip;
    int port;
};

#endif // CLIENT_H
