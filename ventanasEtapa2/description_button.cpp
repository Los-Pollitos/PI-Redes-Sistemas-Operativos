#include "description_button.h"

description_button::description_button(QString name, QWidget * parent, int id, int type):
    QPushButton{name, parent},
    valid(true),
    identifier(id),
    type(type) {
}

void description_button::mousePressEvent(QMouseEvent* e) {
    emit this->pressed(this->identifier, this->type);
    Q_UNUSED(e);
}

