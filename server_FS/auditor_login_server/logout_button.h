#ifndef LOGOUT_BUTTON_H
#define LOGOUT_BUTTON_H


#include <QPushButton>
#include <QObject>

class logout_button : public QPushButton {
    Q_OBJECT
public:
    explicit logout_button(QString name);
    bool valid;

protected:
    void mousePressEvent(QMouseEvent*e) override;

signals:
    void pressed();
};

#endif // LOGOUT_BUTTON_H
