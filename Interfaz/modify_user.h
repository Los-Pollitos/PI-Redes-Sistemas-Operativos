#ifndef MODIFY_USER_H
#define MODIFY_USER_H

#include <QDialog>
#include "login_info.h"

namespace Ui {
class modify_user;
}

class modify_user : public QDialog {
    Q_OBJECT

public:
    explicit modify_user(QWidget *parent = nullptr);
    ~modify_user();
    void set_login_info(login_info* info);

private slots:
    void update_data();
    void on_comboBox_activated(int index);
    void on_approve_changes_clicked();

private:
    int modified_index;
    void add_data();

    Ui::modify_user *ui;
    QList<QString> names;
    QList<int> ids;
    QList<QString> job;
    QList<QString> subordinate;
    QList<int> salary;
    QList<int> vacations;
    QList<QString> record;
    login_info* user_data;
};

#endif // MODIFY_USER_H
