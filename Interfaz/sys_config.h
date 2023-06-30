#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include <QDialog>

#include "login_info.h"
#include "client.h"

namespace Ui {
class sys_config;
}

class sys_config : public QDialog
{
    Q_OBJECT

public:
    explicit sys_config(QWidget *parent = nullptr);
    ~sys_config();
    void set_client(client* local_client);
    void set_user_login(login_info* user_login);

private slots:

    void on_reset_clicked();

private:
    Ui::sys_config *ui;
    login_info* user_login;
    client* local_client;
};

#endif // SYS_CONFIG_H
