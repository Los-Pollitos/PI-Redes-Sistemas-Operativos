#ifndef MODIFY_USER_H
#define MODIFY_USER_H

#include <vector>
#include <QDialog>
#include "login_info.h"
#include "user_data.h"

namespace Ui {
class modify_user;
}

class modify_user : public QDialog {
    Q_OBJECT

public:
    explicit modify_user(QWidget *parent = nullptr);
    ~modify_user();
    void set_login_info(login_info* info);

private slots:
    void update_data();
    void on_comboBox_activated(int index);
    void on_approve_changes_clicked();

private:
    int modified_index;
    void add_data();
    void read_data();

    Ui::modify_user *ui;
    QList<int> ids;
    QList<int> role_admin_config;
    QList<int> role_admin_users;
    QList<int> role_employee;
    QList<int> role_human_resources;
    QList<int> role_debug;
    QList<int> supervisor;
    QList<int> salary;
    QList<int> vacations;
    QList<QString> record;
    login_info* user_login;
    std::vector<user_data> users_data;
};

#endif // MODIFY_USER_H
