#ifndef REQUEST_DESCRIPTION_H
#define REQUEST_DESCRIPTION_H

#include <QDialog>

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
    explicit request_description(int day, int month, int year, int type, QString user, QString description, QWidget *parent = nullptr);
    ~request_description();

private:
    Ui::request_description *ui;
    int date[3];
    int type;
    QString user;
    QString description;
};

#endif // REQUEST_DESCRIPTION_H
