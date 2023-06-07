#ifndef LOGIN_H
#define LOGIN_H

#include "client.h"
#include "change_password.h"
#include "token.h"
#include "login_info.h"

#include <fstream>
#include <QLabel>
#include <QDialog>

// enum with all login messages is in client


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void set_client(client* local_client);

private:
    int validate_user(std::string username, std::string password);
    void ask_for_token();

private slots:
    void on_login_button_clicked();
    void on_forgot_button_clicked();
    void generate_new();

private:
    Ui::login* ui;
    Token* token_page;
    change_password* change_pass;
    login_info* user_data;
    logout_button* request_button;
    client* local_client;
};

#endif // LOGIN_H
