#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

class description_button : public QPushButton {
    Q_OBJECT
public:
    description_button(QString name, QWidget * parent, int id, int type);
    void setValid(bool valid);
    bool getValid();

protected:
    int identifier;
    int type;
    bool valid;
    void mousePressEvent(QMouseEvent*e) override;

signals:
    void pressed(int id, int type);

};

#endif // DESCRIPTION_BUTTON_H
