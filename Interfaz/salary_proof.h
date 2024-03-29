#ifndef SALARY_PROOF_H
#define SALARY_PROOF_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "login_info.h"

namespace Ui {
class salary_proof;
}

class salary_proof : public QDialog
{
    Q_OBJECT

public:
    explicit salary_proof(QWidget *parent = nullptr);
    ~salary_proof();
    void set_client(client* local_client);
    void setUserData(login_info *user_login);

private slots:
    void on_pushButton_clicked();

private:
    Ui::salary_proof *ui;
    client* local_client;
    login_info* user_login;
};

#endif // SALARY_PROOF_H
