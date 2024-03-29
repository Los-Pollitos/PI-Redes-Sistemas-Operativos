#ifndef MODIFY_USER_H
#define MODIFY_USER_H

#include <string>
#include <vector>
#include <QDate>
#include <QDialog>
#include "client.h"
#include "login_info.h"
#include "security.h"
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
    void set_user_role(char role);
    void set_client(client* local_client);
    void add_data_to_combobox();
    void load_user_data(std::string& data);

private slots:
    void update_data();
    Qt::CheckState unmask_role(int role_id, char role);
    void set_read_only();
    void update_roles();
    void update_phone();
    void update_email();
    void update_office();
    void update_vacations();
    void update_laboral_data();
    void add_record();
    void on_comboBox_activated(int index);
    void on_approve_changes_clicked();
    void check_error(std::string received, QString error);
    void set_colors();
    void set_data_ui();
    void empty_text();
    void encrypt_salary(std::string& salary,std::string& deductibles);
    void decrypt_salary(std::string salary, std::string deductibles);

private:
    Ui::modify_user* ui;
    client* local_client;
    login_info* user_login;
    int user_login_role;
    user_data user_info;
    std::vector<std::string> user_names;
    bool correct_changes;
    bool changed;
};

#endif // MODIFY_USER_H
