#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

class description_button : public QPushButton {
    Q_OBJECT
public:
    description_button(QString name, QWidget * parent, int id, int type);
    bool valid;
    int identifier;

protected:
    int type;
    void mousePressEvent(QMouseEvent*e) override;

signals:
    void pressed(int id, int type);
    void disapear(int id);

};

#endif // DESCRIPTION_BUTTON_H
