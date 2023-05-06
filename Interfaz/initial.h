#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>
#include "human_resources.h"
#include "manager.h"
#include "payment_proof.h"
#include "salary_proof.h"
#include "work_proof.h"


namespace Ui {
class initial;
}

class initial : public QDialog
{
    Q_OBJECT

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();

private slots:
    void on_funciones_especiales_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::initial *ui;
    human_resources * hhrr;
    manager * office_manager;
    work_proof *workP;
    payment_proof *paymentP;
    salary_proof *salaryP;
    int type_employee;
};

#endif // INITIAL_H
