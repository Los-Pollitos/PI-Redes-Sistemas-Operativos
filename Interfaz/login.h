#ifndef LOGIN_H
#define LOGIN_H

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

private:
    Ui::login *ui;
    QLabel *label;
    Token *tokenPage;
};

#endif // LOGIN_H
