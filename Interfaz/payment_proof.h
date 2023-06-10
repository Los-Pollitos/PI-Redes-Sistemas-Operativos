#ifndef PAYMENT_PROOF_H
#define PAYMENT_PROOF_H

#include <QDialog>
#include "client.h"
#include "login_info.h"

namespace Ui {
class payment_proof;
}

class payment_proof : public QDialog
{
    Q_OBJECT

public:
    explicit payment_proof(QWidget *parent = nullptr);
    ~payment_proof();
    void set_client(client* local_client);
    void setUserData(login_info *user_login);

private slots:
    void on_pushButton_clicked();

private:
    Ui::payment_proof *ui;
    client* local_client;
    login_info *user_login;
};

#endif // PAYMENT_PROOF_H
