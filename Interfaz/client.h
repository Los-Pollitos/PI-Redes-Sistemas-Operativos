#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define CLIENT_DATA_SIZE 256

class client
{
public:
    client();
    std::string send_and_receive(std::string to_send);
private:
    void adapt_data(char* data, std::string& new_info);
};

#endif // CLIENT_H
