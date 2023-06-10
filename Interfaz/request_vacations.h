#ifndef REQUEST_VACATIONS_H
#define REQUEST_VACATIONS_H

#include <QDialog>
#include "client.h"

namespace Ui {
class request_vacations;
}

class request_vacations : public QDialog
{
    Q_OBJECT

public:
    explicit request_vacations(QWidget *parent = nullptr);
    ~request_vacations();
    void set_client(client* local_client);

private:
    Ui::request_vacations *ui;
    client* local_client;
    std::string to_send;
};

#endif // REQUEST_VACATIONS_H
