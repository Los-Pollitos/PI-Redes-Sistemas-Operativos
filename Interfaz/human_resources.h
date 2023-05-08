#ifndef HUMAN_RESOURCES_H
#define HUMAN_RESOURCES_H

#include <QDialog>
#include "manage_user.h"
#include "handle_requests.h"
#include "login_info.h"

namespace Ui {
class human_resources;
}

class human_resources : public QDialog
{
    Q_OBJECT

public:
    explicit human_resources(QWidget *parent = nullptr);
    void set_user_data(login_info * user_data);
    ~human_resources();

private slots:


    void on_process_button_clicked();

private:
    Ui::human_resources *ui;
    handle_requests * request_handler;
    login_info * user_data;
};

#endif // HUMAN_RESOURCES_H
