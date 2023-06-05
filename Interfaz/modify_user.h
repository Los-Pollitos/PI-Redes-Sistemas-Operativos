#ifndef MODIFY_USER_H
#define MODIFY_USER_H

#include <string>
#include <vector>
#include <QDialog>
#include "client.h"
#include "login_info.h"
#include "user_data.h"


namespace Ui {
class modify_user;
}

class modify_user : public QDialog {
    Q_OBJECT

public:
    explicit modify_user(QWidget *parent = nullptr);
    ~modify_user();
    void set_login_info(login_info* info);
    void set_client(client* client);


private slots:
    void update_data();
    void add_data_to_combobox();
    //    void write_data();  // TODO(Angie): ver si dejar
    Qt::CheckState unmask_role(int user_index, char role);
    //    void read_data();  // TODO(Angie): ver si dejar

    void on_comboBox_activated(int index);
    void on_approve_changes_clicked();

private:
    Ui::modify_user* ui;
    client* local_client;
    int modified_index;
    login_info* user_login;
    user_data user_info;
    std::vector<std::string> user_names;
};

#endif // MODIFY_USER_H
