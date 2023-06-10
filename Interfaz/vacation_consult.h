#ifndef VACATION_CONSULT_H
#define VACATION_CONSULT_H

#include <QDialog>
#include "client.h"
#include "login_info.h"

namespace Ui {
class vacation_consult;
}

class vacation_consult : public QDialog
{
    Q_OBJECT

public:
    explicit vacation_consult(QWidget *parent = nullptr);
    ~vacation_consult();
    void set_client(client* local_client);
    void set_user_login(login_info* user_login);

private:
    // Attributes
    Ui::vacation_consult *ui;
    client* local_client;
    login_info* user_login;

    // Methods
    void show_result(std::string result);
    std::string obtain_from_server();
};

#endif // VACATION_CONSULT_H
