#include "description_button.h"

description_button::description_button(QString name, QWidget * parent, int id, int type, int id_requests):
    QPushButton{name, parent},
    valid(true),
    identifier(id),
    type(type),
    id_requests(id_requests){
    this->setStyleSheet("color: #001f21;");
}


void description_button::mousePressEvent(QMouseEvent* e) {
    emit this->pressed(this->identifier, this->type);
    Q_UNUSED(e);
}


int description_button::get_id_requests() {
    return this->id_requests;
}

void description_button::set_id_requests(int id_requests) {
    this->id_requests = id_requests;
}


int description_button::get_type() {
    return this->type;
}

void description_button::set_type(int type) {
    this->type = type;
}
