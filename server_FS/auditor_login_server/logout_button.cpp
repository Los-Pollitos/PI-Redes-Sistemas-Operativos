#include "logout_button.h"

logout_button::logout_button(QString name):
    QPushButton{name},
    valid(true) {
}

void logout_button::mousePressEvent(QMouseEvent* e) {
    emit this->pressed();
    Q_UNUSED(e);
}
