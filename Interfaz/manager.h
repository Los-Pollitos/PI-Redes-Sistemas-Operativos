#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

#include "handle_requests.h"
#include "modify_user.h"
#include "login_info.h"

namespace Ui {
class manager;
}

class manager : public QDialog {
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();
    void set_login_info(login_info* info);

private slots:
    void on_employee_information_2_clicked();
    void on_employee_information_clicked();

private:
    Ui::manager* ui;
    handle_requests* request_handler;
    modify_user* modify_info;
    login_info* user_data;
};

#endif // MANAGER_H
