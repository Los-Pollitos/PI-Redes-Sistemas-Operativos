#ifndef OFFICE_DESCRIPTION_H
#define OFFICE_DESCRIPTION_H

#include <QDialog>
#include <string>
#include <vector>

#include "client.h"

namespace Ui {
class office_description;
}

class office_description : public QDialog {
    Q_OBJECT

public:
    explicit office_description(QWidget *parent = nullptr);
    ~office_description();
    void load_data();
    void set_client(client* local_client);
    void set_user_name(std::string user_name);

private slots:
    void on_comboBox_activated(int index);

private:
    client* local_client;
    Ui::office_description *ui;
    std::vector<std::string> names;
    std::vector<std::string> ids;
    std::string user_name;

    void set_colors();
};

#endif // OFFICE_DESCRIPTION_H
