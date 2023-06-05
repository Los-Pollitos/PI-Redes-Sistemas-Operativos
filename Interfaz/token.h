#ifndef TOKEN_H
#define TOKEN_H

#include <QDialog>
#include <QMessageBox>

#include "initial.h"
#include "login_info.h"
#include "client.h"

namespace Ui {
class Token;
}

class Token : public QDialog
{
    Q_OBJECT

public:
    explicit Token(QWidget *parent = nullptr);
    ~Token();
    void setUserData(login_info * user_data);
    void setParent_Button(logout_button * parent_button);
    void set_client(client * local_client);

private slots:
    void on_validate_label_clicked();
    void on_cancel_button_clicked();

private:
    Ui::Token* ui;
    initial* initial_page;
    login_info * user_data;
    int pos;
    logout_button* parent_button;
    client* local_client;
};

#endif // TOKEN_H
