#ifndef MANAGE_USER_H
#define MANAGE_USER_H

#include "login_info.h"

#include <QDialog>

namespace Ui {
class manage_user;
}

class manage_user : public QDialog
{
    Q_OBJECT

public:
    explicit manage_user(QWidget *parent = nullptr);
    void set_user_data(login_info * user_data);
    ~manage_user();


private slots:
    void on_generate_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::manage_user *ui;
    login_info* user_data;
};

#endif // MANAGE_USER_H
