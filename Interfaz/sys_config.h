#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include <QDialog>
#include <QMessageBox>
#include <vector>
#include <fstream>

#include "login_info.h"
#include "client.h"
#include "security.h"

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

    void on_confirm_clicked();

private:
    // Attributes
    Ui::sys_config *ui;
    login_info* user_login;
    client* local_client;
    std::vector<std::string> current_text;
    // Methods
    bool check_if_empty();
    bool check_password();
    void show_error(std::string error);
    void show_success(std::string success);
    void prepare_string(std::string& to_send);
    void set_up_client();
};

#endif // SYS_CONFIG_H
