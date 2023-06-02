#include <QCoreApplication>
#include <iostream>

#include "data_base.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    data_base base;
    base.add_office(1,"San Jose");
//    base.add_office(2,"Alajuela");
//    base.add_office(3,"Cartago");

    std::cout << base.consult_office_name(1);

    return a.exec();
}
