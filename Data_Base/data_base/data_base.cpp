#include "data_base.h"


data_base::data_base() {
    this->base = QSqlDatabase::addDatabase("SQLITE");
    this->base.setDatabaseName("data.db");
    if (! this->base.open()) {
        qDebug() << "[BASE_DATOS] Fallo al conectar";
    } else {
        qDebug() << "[BASE_DATOS] Conexión existosa";
    }
}


void data_base::add_office(int id, std::string name) {
    QSqlQuery new_office;
    new_office.prepare("INSERT INTO offices (id,name) VALUES (:id,:name)");
    new_office.bindValue(":id", id);
    new_office.bindValue(":name", QString::fromStdString(name));
    if(!new_office.exec()) {
        qDebug() << "[BASE_DATOS] Error agregando producto: " << new_office.lastError();
    }
}
