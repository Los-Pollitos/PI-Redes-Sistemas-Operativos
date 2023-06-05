#ifndef MANAGE_USER_H
#define MANAGE_USER_H

#include "login_info.h"

#include "file_system.h"
#include "client.h"

#include <QDialog>

namespace Ui {
class manage_user;
}

class manage_user : public QDialog
{
    Q_OBJECT

public:
    explicit manage_user(QWidget *parent = nullptr);
    void set_user_login(login_info * user_login);
    void set_file_system(FS* file_system);
    void set_client(client* local_client);
    ~manage_user();

private:
    bool find_user(std::string& desired_username);
    // Uses file system object
    void insert_user_file_system(std::string& desired_username, std::string& desired_password);
    void delete_user_file_system(std::string& desired_username);
    // Uses fstream
    void insert_user_login(std::string& desired_username, std::string& desired_password);
    void insert_user_data(std::string& desired_username, std::string& name, std::string& id);
    void clean_aux_file();
    void reinsert_login_file();
    void reinsert_data_file();
    void delete_user_login(std::string& desired_username);
    void delete_user_data(std::string& desired_username);

private slots:
    void on_generate_button_clicked();
    void on_delete_button_clicked();

private:
    Ui::manage_user* ui;
    login_info* user_login;
    FS* file_system;
    client* local_client;
};

#endif // MANAGE_USER_H
