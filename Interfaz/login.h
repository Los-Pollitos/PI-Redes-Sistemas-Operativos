#ifndef LOGIN_H
#define LOGIN_H

#include "client.h"
#include "change_password.h"
#include "file_system.h"
#include "token.h"
#include "login_info.h"

#include <fstream>
#include <QLabel>
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void set_file_system(FS* file_system);
    void set_client(client* client);


private:
    bool validate_data(QString username, QString password);
    void load_file(std::string location, std::string file_name);
    void refresh_file_system();

private slots:
    void on_login_button_clicked();
    void on_forgot_button_clicked();
    void generate_new();

private:
    Ui::login* ui;
    Token* token_page;
    change_password* change_pass;
    login_info* user_data;
    FS* file_system;
    logout_button* request_button;
    client* local_client;
};

#endif // LOGIN_H
