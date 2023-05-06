#ifndef LOGIN_H
#define LOGIN_H

#include "change_password.h"
#include "token.h"
#include "login_info.h"
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

private:
    bool validate_data(QString username, QString password);

private slots:
    void on_login_button_clicked();
    void on_forgot_button_clicked();

private:
    Ui::login *ui;
    Token *tokenPage;
    change_password *changePass;
    login_info * user_data;
};

#endif // LOGIN_H
