/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include <QCoreApplication>
#include <iostream>

#include "data_base.h"
#include "data_server.h"

int main(int argc, char *argv[]) {
    // TODO(nosotros): devolver
    //    QCoreApplication a(argc, argv);

    //    data_server * server = new data_server();
    //    server->wait_for_request();

    //    delete server;

    //    return a.exec();

    // TODO(nosotros): BORRAR
    QCoreApplication a(argc, argv);

    data_base * db = new data_base();
    db->add_office(1, "San Jose");
    qDebug() << "Agregue oficina \n";
    db->add_employee("lsolano", "Luis Solano", "118860202", "71935068", "luis@gmail.com", 1, 'c', 15, 1);
    qDebug() << "Agregue empleadin\n";
    qDebug() << db->consult_employee_data("lsolano");
    db->delete_user("lsolano");
    qDebug() << db->consult_employee_data("lsolano");
    delete db;

    return a.exec();
}
