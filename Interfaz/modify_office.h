#ifndef MODIFY_OFFICE_H
#define MODIFY_OFFICE_H

#include <QDialog>

#include "client.h"
#include "login_info.h"

namespace Ui {
class modify_office;
}

class modify_office : public QDialog {
    Q_OBJECT

public:
    explicit modify_office(QWidget *parent = nullptr);
    ~modify_office();
    void set_client(client* local_client);
    void set_user_login(login_info* user_login);

private slots:
    void on_change_name_clicked();
    void on_create_clicked();
    void on_detele_clicked();

private:
    Ui::modify_office *ui;
    client* local_client;
    login_info* user_login;

    void set_colors();
    void check_error(std::string received, QString error);
    void empty_lines();
};

#endif // MODIFY_OFFICE_H
