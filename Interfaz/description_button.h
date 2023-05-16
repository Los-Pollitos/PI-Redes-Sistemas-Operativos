#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

#define EMPLOYEE_SEP 0
#define WORK_PAGE 1
#define PAYMENT_PAGE 2
#define SALARY_PAGE 3
#define SEE_SALARY 4
#define PENDING_REQUESTS 5
#define VACATION_MANGER 6
#define SEE_VACATIONS 7
#define SEE_RECORD 8
#define SUPERVISOR_SEP 9
#define REQUEST_HANDLER 10
#define USER_SEP 11
#define USER_MANAGER 12
#define USER_MOD 13


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
    void update_all();

};

#endif // DESCRIPTION_BUTTON_H
