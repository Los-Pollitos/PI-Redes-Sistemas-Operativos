#ifndef REQUEST_DESCRIPTION_H
#define REQUEST_DESCRIPTION_H

#include <QDialog>

#include "description_button.h"

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
    void set_atributes(int day, int month, int year, int& type, QString user, QString& description, description_button *& parent_button);
    ~request_description();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::request_description *ui;
    int date[3];
    int type;
    description_button * parent_button;
    QString user;
    QString description;
};

#endif // REQUEST_DESCRIPTION_H
