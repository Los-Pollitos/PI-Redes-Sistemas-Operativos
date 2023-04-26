#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

#include "handle_requests.h"

namespace Ui {
class manager;
}

class manager : public QDialog
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

private slots:
    void on_employee_information_2_clicked();

private:
    Ui::manager *ui;
    handle_requests * request_handler;
};

#endif // MANAGER_H
