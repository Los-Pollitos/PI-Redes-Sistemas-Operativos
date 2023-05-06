#ifndef TOKEN_H
#define TOKEN_H

#include <QDialog>
#include <QMessageBox>

#include "initial.h"
#include "login_info.h"

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

private slots:
    void on_validate_label_clicked();

private:
    Ui::Token* ui;
    initial* initial_page;
    login_info * user_data;
    int pos;
};

#endif // TOKEN_H
