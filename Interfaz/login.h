#ifndef LOGIN_H
#define LOGIN_H

#include "change_password.h"
#include "token.h"
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

private slots:
    void on_login_button_clicked();

    void on_forgot_button_clicked();

private:
    Ui::login *ui;
    QLabel *label;
    Token *tokenPage;
    change_password *changePass;
};

#endif // LOGIN_H
