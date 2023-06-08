#ifndef MANAGE_USER_H
#define MANAGE_USER_H

#include "login_info.h"
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
    ~manage_user();
    void set_user_login(login_info * user_login);
    void set_client(client* local_client);

private slots:
    void on_generate_button_clicked();
    void on_delete_button_clicked();
    void show_error(std::string error);
    void show_success(std::string success);

private:
    Ui::manage_user* ui;
    login_info* user_login;
    client* local_client;
};

#endif // MANAGE_USER_H
