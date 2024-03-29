#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>
#include <QPushButton>
#include <vector>
#include <QVBoxLayout>

#include "auditor.h"
#include "sys_config.h"
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
#include "generate_new_token.h"
#include "request_vacations.h"
#include "vacation_consult.h"
#include "logout_button.h"
#include "client.h"
#include "modify_office.h"
#include "office_description.h"

namespace Ui {
class initial;
}

class initial : public QDialog
{
    Q_OBJECT

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();
    void setParent_Button(logout_button * parent_button);
    void setUserDataLogin(login_info * user_login);
    void update_scrollbar();
    void create_windows(int id, int type);
    void set_client(client* local_client);

private slots:
    void on_pushButton_clicked();

private:
    char ask_for_role(int & correct);
    char role;
    Ui::initial *ui;
    work_proof *work_page;
    payment_proof *payment_page;
    salary_proof *salary_page;
    consult_salary * see_salary;
    login_info * users_login;
    consult_requests * pending_requests;
    consult_record * see_record;
    handle_requests * request_handler;
    manage_user * user_manager;
    modify_user * user_mod;
    generate_new_token * new_token;
    request_vacations * vacation_manager;
    vacation_consult * see_vacations;
    QVBoxLayout * layout;
    QWidget * container;
    std::vector<description_button*> requests_buttons;
    description_button * update_buttons;
    logout_button * parent_button;
    client* local_client;
    modify_office* office_mod;
    office_description* see_office;
    auditor * auditor_page;
    sys_config * sys_config_page;
};

#endif // INITIAL_H
