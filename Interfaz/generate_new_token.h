#ifndef GENERATE_NEW_TOKEN_H
#define GENERATE_NEW_TOKEN_H

#include <QDialog>
#include <string>
#include "client.h"
#include "login_info.h"

namespace Ui {
class generate_new_token;
}

class generate_new_token : public QDialog
{
    Q_OBJECT

public:
    explicit generate_new_token(QWidget *parent = nullptr);
    ~generate_new_token();
    void set_login_info(login_info * user_data);
    void set_client(client * local_client);

private slots:
    void on_generate_button_clicked();
    void on_generate_button_2_clicked();

private:
    Ui::generate_new_token *ui;
    client* local_client;
    login_info * user_data;
    std::string possible_token;
};

#endif // GENERATE_NEW_TOKEN_H
