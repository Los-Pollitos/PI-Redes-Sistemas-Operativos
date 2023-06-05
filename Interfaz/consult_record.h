#ifndef CONSULT_RECORD_H
#define CONSULT_RECORD_H

#include <QDialog>
#include "client.h"

namespace Ui {
class consult_record;
}

class consult_record : public QDialog
{
    Q_OBJECT

public:
    explicit consult_record(QWidget *parent = nullptr);
    ~consult_record();
    void set_client(client* local_client);

private:
    Ui::consult_record *ui;
    client* local_client;
};

#endif // CONSULT_RECORD_H
