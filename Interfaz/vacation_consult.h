#ifndef VACATION_CONSULT_H
#define VACATION_CONSULT_H

#include <QDialog>
#include "client.h"

namespace Ui {
class vacation_consult;
}

class vacation_consult : public QDialog
{
    Q_OBJECT

public:
    explicit vacation_consult(QWidget *parent = nullptr);
    ~vacation_consult();
    void set_client(client* client);

private:
    Ui::vacation_consult *ui;
};

#endif // VACATION_CONSULT_H
