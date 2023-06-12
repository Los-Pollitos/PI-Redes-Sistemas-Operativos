/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include <QCoreApplication>
#include <iostream>
#include "data_server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    data_server * server = new data_server();
    server->wait_for_request();

    delete server;

    return a.exec();
}
