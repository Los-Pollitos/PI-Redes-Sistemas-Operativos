#ifndef REQUEST_DESCRIPTION_H
#define REQUEST_DESCRIPTION_H

#include <QDialog>

#include "description_button.h"
#include "login_info.h"

#define REQUEST_VACATIONS 1
#define PAYMENT_PROOF 2
#define WORK_PROOF 3
#define SALARY_PROOF 4


namespace Ui {
class request_description;
}

class request_description : public QDialog
{
    Q_OBJECT

public:
    request_description();
    explicit request_description(QWidget *parent = nullptr);
    void set_atributes(int day, int month, int year, int& type, QString user, QString& description, description_button *& parent_button, login_info * user_login, bool admin);
    ~request_description();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


    void on_file_button_clicked();

private:
    Ui::request_description *ui;
    int date[3];
    int type;
    bool admin;
    bool uploaded_file;
    description_button * parent_button;
    QString user;
    QString description;
    login_info * user_login;
};

#endif // REQUEST_DESCRIPTION_H
