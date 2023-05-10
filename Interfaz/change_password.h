#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include "login_info.h"

#include <QDialog>

namespace Ui {
class change_password;
}

class change_password : public QDialog
{
    Q_OBJECT

public:
    explicit change_password(QWidget *parent = nullptr);
    ~change_password();
    bool change_data(QString username, QString password);

private slots:
    void on_pushButton_reinicarContra_clicked();

private:
    Ui::change_password *ui;
    int pos;
    int token[TOKEN_SIZE];
};

#endif // CHANGE_PASSWORD_H
