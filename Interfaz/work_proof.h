#ifndef WORK_PROOF_H
#define WORK_PROOF_H

#include <QDialog>
#include "client.h"

namespace Ui {
class work_proof;
}

class work_proof : public QDialog
{
    Q_OBJECT

public:
    explicit work_proof(QWidget *parent = nullptr);
    ~work_proof();
    int tipo;
    void set_client(client* local_client);

private slots:
    void on_pushButton_clicked();

private:
    Ui::work_proof *ui;
    client* local_client;
};

#endif // WORK_PROOF_H
