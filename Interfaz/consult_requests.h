#ifndef CONSULT_REQUESTS_H
#define CONSULT_REQUESTS_H


#include <QDialog>
#include <QPushButton>
#include <vector>
#include <QVBoxLayout>

#include "description_button.h"
#include "request_description.h"
#include "login_info.h"
#include "client.h"

namespace Ui {
class consult_requests;
}

class consult_requests : public QDialog { Q_OBJECT

public:
    explicit consult_requests(QWidget *parent = nullptr);
    ~consult_requests();
    void set_user_login(login_info * user_login);
    void set_client(client* local_client);

private:
    QVBoxLayout * layout;
    QWidget * container;
    Ui::consult_requests *ui;
    std::vector<description_button*> requests_buttons;
    request_description * description;
    login_info * user_login;
    client* local_client;

    void update_scroll();

protected slots:
    void show_description(int id, int type);
};

#endif // CONSULT_REQUESTS_H
