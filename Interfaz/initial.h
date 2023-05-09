#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>
#include <QPushButton>
#include <vector>
#include <QVBoxLayout>


#include "login_info.h"
#include "payment_proof.h"
#include "salary_proof.h"
#include "work_proof.h"
#include "consult_requests.h"
#include "consult_record.h"
#include "consult_salary.h"
#include "handle_requests.h"
#include "manage_user.h"
#include "modify_user.h"
#include "request_vacations.h"
#include "vacation_consult.h"

#define ADMIN_USERS 0
#define ADMIN_CONFIG 1
#define SUPERVISOR 2
#define RRHH 3
#define DEBUG 4
#define EMPLOYEE 5


namespace Ui {
class initial;
}

class initial : public QDialog
{
    Q_OBJECT

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();
    void setUserData(login_info * user_data);
    void update_scrollbar();

private slots:
    void on_funciones_especiales_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::initial *ui;
    work_proof *work_page;
    payment_proof *payment_page;
    salary_proof *salary_page;
    consult_salary * see_salary;
    login_info * user_data;
    consult_requests * pending_requests;
    consult_record * see_record;
    handle_requests * request_handler;
    manage_user * user_manager;
    modify_user * user_mod;
    request_vacations * vacation_manager;
    vacation_consult * see_vacations;
    QVBoxLayout * layout;
    QWidget * container;
    bool roles[6];
    std::vector<description_button*> requests_buttons;
};

#endif // INITIAL_H
