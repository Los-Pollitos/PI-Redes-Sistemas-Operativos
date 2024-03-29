#ifndef CONSULT_SALARY_H
#define CONSULT_SALARY_H

#include <QDialog>
#include "client.h"
#include "login_info.h"
#include "security.h"
#include "user_data.h"

namespace Ui {
class consult_salary;
}

class consult_salary : public QDialog
{
    Q_OBJECT

public:
    explicit consult_salary(QWidget *parent = nullptr);
    ~consult_salary();
    void set_client(client* local_client);
    void setUserData(login_info * user_login);

private:
    Ui::consult_salary *ui;
    client* local_client;
    login_info * user_login;

};

#endif // CONSULT_SALARY_H
