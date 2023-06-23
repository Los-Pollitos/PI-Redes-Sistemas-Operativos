#ifndef TOKEN_H
#define TOKEN_H

#include <QDialog>
#include <QMessageBox>

#include "login_info.h"
#include "client.h"
#include "logout_button.h"
#include "auditor.h"

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
    login_info * user_data;
    auditor * audit;
    int pos;
    logout_button* parent_button;
    client* local_client;
};

#endif // TOKEN_H
