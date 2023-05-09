#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

#define WORK_PAGE 0
#define PAYMENT_PAGE 1
#define SALARY_PAGE 2
#define SEE_SALARY 3
#define PENDING_REQUESTS 4
#define SEE_RECORD 5
#define REQUEST_HANDLER 6
#define USER_MANAGER 7
#define VACATION_MANGER 8
#define SEE_VACATIONS 9
#define USER_MOD 10


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
