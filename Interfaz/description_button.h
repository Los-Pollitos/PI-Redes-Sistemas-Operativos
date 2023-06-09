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

#define PENDING 0
#define ACCEPTED 1
#define DENIED 2

#define VACATION 0
#define PROOF 1

class description_button : public QPushButton {
    Q_OBJECT
public:
    description_button(QString name, QWidget * parent, int id, int type, int id_request = 0);
    int get_id_requests();
    void set_id_requests(int type_request);
    int get_type();
    void set_type(int type);
    bool valid;
    int identifier;

protected:
    int type;
    int id_requests;
    void mousePressEvent(QMouseEvent*e) override;

signals:
    void pressed(int id, int type);
    void disapear(int id);
    void update_all();

};

#endif // DESCRIPTION_BUTTON_H
