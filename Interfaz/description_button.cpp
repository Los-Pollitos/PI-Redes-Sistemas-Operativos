#include "description_button.h"

description_button::description_button(QString name, QWidget * parent, int id, int type, int type_request):
    QPushButton{name, parent},
    valid(true),
    identifier(id),
    type(type),
    type_request(type_request){
    this->setStyleSheet("color: #001f21;");
}


void description_button::mousePressEvent(QMouseEvent* e) {
    emit this->pressed(this->identifier, this->type);
    Q_UNUSED(e);
}


int description_button::get_type_request() {
    return this->type_request;
}

void description_button::set_type_request(int type_request) {
    this->type_request = type_request;
}


