#ifndef WORK_PROOF_H
#define WORK_PROOF_H

#include <QDialog>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::work_proof *ui;
};

#endif // WORK_PROOF_H
