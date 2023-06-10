#include "work_proof.h"
#include "ui_work_proof.h"

work_proof::work_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::work_proof)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->pushButton->setStyleSheet("color: #001f21;");
    this->ui->textBrowser_descripcion->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Constancia laboral");
    this->local_client = new client();
    this->user_login = new login_info();
}

work_proof::~work_proof() {
    if (this->ui) {
        delete ui;
        this->ui = 0;
     }
}

void work_proof::set_client(client* local_client) {
     this->local_client = local_client;
}

void work_proof::setUserData(login_info *user_login) {
     this->user_login = user_login;
}

void work_proof::on_pushButton_clicked() {
    std::string user = this->user_login->user;
    std::cout << user << std::endl;
    std::time_t actual_time = std::time(nullptr);
    std::tm* now = std::localtime(&actual_time);

    int actual_day = now->tm_mday;
    int actual_month = now->tm_mon;
    int actual_year = now->tm_year + 1900;

    std::string to_send = "";
    to_send += ((char)WORK_PROOF);
    to_send += user + ",";
    to_send += std::to_string(actual_day) + ",";
    to_send += std::to_string(actual_month) + ",";
    to_send += std::to_string(actual_year) + ",";

    std::string result = local_client->send_and_receive(to_send);

    if (result == "1") {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Enviado");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("La solicitud fue realizada correctamente");
        show_message.exec();
    }

    this->close();
}
