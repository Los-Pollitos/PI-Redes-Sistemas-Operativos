/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef INTERMEDIARY_H
#define INTERMEDIARY_H

#include <string>

#include "server_FS/login_server.h"

// TODO(us): tener data base
// #include "data_base/data_base.h"

enum request_types {
  LOGIN = 0,
  TOKEN,
  CHANGE_PASSWORD,
  CREATE_USER,
  DELETE_USER,
  
};

class intermediary {
  private:
    login_server* login_server;
    int connection;
    char data[DATA_SIZE];
    int message_count;
    struct sockaddr_storage ipRemoto;
  
  public:
    intermediary();
    ~intermediary();
    void wait_for_request();
    void answer_request();
};

#endif
