#include "office_description.h"
#include "ui_office_description.h"

office_description::office_description(QWidget *parent) : QDialog(parent), ui(new Ui::office_description) {
    this->ui->setupUi(this);
    this->ui->name->setReadOnly(true);
    this->set_colors();
}

office_description::~office_description() {
    delete this->ui;
}

void office_description::set_colors() {
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->name->setStyleSheet("color: #001f21;");
    this->ui->office->setStyleSheet("color: #001f21;");
    this->ui->label_9->setStyleSheet("color: #001f21;");
    this->ui->comboBox->setStyleSheet("color: #001f21;");
}

void office_description::set_client(client* local_client) {
    this->local_client = local_client;
}

void office_description::set_user_name(std::string user_name) {
    this->user_name = user_name;
}

void office_description::load_data() {
    // clear the comboBox
    for (int i = this->ui->comboBox->count(); i > 0; --i) {
        this->ui->comboBox->removeItem(i-1);
    }
    this->names.clear();
    this->ids.clear();
    this->ui->name->setText("");

    std::string to_send = " " + this->user_name;
    to_send[0] = ALL_OFFICES;
    std::string data_received = this->local_client->send_and_receive(to_send);
    data_received += ",";

    // store the usernames individually
    std::string new_office = "";
    std::string new_office_id = "";
    for(size_t i = 0; i < data_received.length(); ++i) {
        if (data_received[i] != ',') {
            while(data_received[i] != '.') {  // find the name
                new_office += data_received[i++];
            }
            ++i;  // move from the ','
            while(data_received[i] != ',') {  // find the id
                new_office_id += data_received[i++];
            }

            this->names.push_back(new_office);
            this->ids.push_back(new_office_id);
            new_office = "";
            new_office_id = "";
        }
    }

    // add the ids to the comboBox
    for (size_t i = 0; i < this->ids.size(); ++i) {
        ui->comboBox->addItem(QString::fromStdString(this->ids[i]));
    }
}

void office_description::on_comboBox_activated(int index) {
    this->ui->name->setText(QString::fromStdString(this->names[index]));
}
