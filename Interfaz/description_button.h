#ifndef DESCRIPTION_BUTTON_H
#define DESCRIPTION_BUTTON_H

#include <QPushButton>
#include <QWidget>

enum type_button {
     EMPLOYEE_SEP = 0,
     WORK_PAGE,
     PAYMENT_PAGE,
     SALARY_PAGE,
     SEE_SALARY,
     PENDING_REQUESTS,
     VACATION_MANGER,
     SEE_VACATIONS,
     SEE_RECORD,
     SUPERVISOR_SEP,
     REQUEST_HANDLER,
     USER_SEP,
     USER_MANAGER,
     USER_MOD,
     CHANGE_TOKEN,
};


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
