#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

class description_button : public QPushButton {
    Q_OBJECT
public:
    description_button(QString name, QWidget * parent, int id, int type);

protected:
    int identifier;
    int type;
    void mousePressEvent(QMouseEvent*e) override;

signals:
    void pressed(int id, int type);

};

#endif // DESCRIPTION_BUTTON_H
