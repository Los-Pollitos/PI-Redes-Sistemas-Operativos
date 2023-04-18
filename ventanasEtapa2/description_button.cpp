#include "description_button.h"

description_button::description_button(QString name, QWidget * parent, int id, int type):
    QPushButton{name, parent},
    identifier(id),
    type(type),
    valid(true){
}

void description_button::mousePressEvent(QMouseEvent* e) {
    emit this->pressed(this->identifier, this->type);
    Q_UNUSED(e);
}

void description_button::setValid(bool valid){
    this->valid = valid;
}

bool description_button::getValid() {
    return this->valid;
}
