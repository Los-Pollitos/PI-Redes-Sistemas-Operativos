#ifndef PAYMENT_PROOF_H
#define PAYMENT_PROOF_H

#include <QDialog>
#include "client.h"

namespace Ui {
class payment_proof;
}

class payment_proof : public QDialog
{
    Q_OBJECT

public:
    explicit payment_proof(QWidget *parent = nullptr);
    ~payment_proof();
    void set_client(client* client);

private slots:
    void on_pushButton_clicked();

private:
    Ui::payment_proof *ui;
};

#endif // PAYMENT_PROOF_H
