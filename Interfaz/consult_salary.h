#ifndef CONSULT_SALARY_H
#define CONSULT_SALARY_H

#include <QDialog>

namespace Ui {
class consult_salary;
}

class consult_salary : public QDialog
{
    Q_OBJECT

public:
    explicit consult_salary(QWidget *parent = nullptr);
    ~consult_salary();

private:
    Ui::consult_salary *ui;
};

#endif // CONSULT_SALARY_H
