#include "generate_new_token.h"
#include "ui_generate_new_token.h"

#include <QMessageBox>

generate_new_token::generate_new_token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generate_new_token)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->password_line->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Generar token nuevo");
    this->ui->token_1->setStyleSheet("color: #001f21;");
    this->ui->token_2->setStyleSheet("color: #001f21;");
    this->ui->token_3->setStyleSheet("color: #001f21;");
    this->ui->token_4->setStyleSheet("color: #001f21;");
    this->ui->token_5->setStyleSheet("color: #001f21;");
    this->ui->token_6->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->user_line->setStyleSheet("color: #001f21;");
    this->ui->password_line->setStyleSheet("color: #001f21;");
    this->ui->generate_button->setStyleSheet("color: #001f21;");
    this->ui->generate_button->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");

    this->ui->token_1->setEnabled(false);
    this->ui->token_1->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_2->setEnabled(false);
    this->ui->token_2->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_3->setEnabled(false);
    this->ui->token_3->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_4->setEnabled(false);
    this->ui->token_4->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_5->setEnabled(false);
    this->ui->token_5->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_6->setEnabled(false);
    this->ui->token_6->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->ui->token_1->setText(" ");
    this->ui->token_2->setText(" ");
    this->ui->token_3->setText(" ");
    this->ui->token_4->setText(" ");
    this->ui->token_5->setText(" ");
    this->ui->token_6->setText(" ");
}

generate_new_token::~generate_new_token() {
    delete ui;
}

void generate_new_token::set_login_info(login_info * user_data) {
    this->user_data = user_data;
}
void generate_new_token::set_client(client * local_client){
    this->local_client = local_client;
}

void generate_new_token::on_generate_button_clicked() {
    this->possible_token = "";

    int number = (int)(rand()%100);
    std::string to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_1->setText(QString::fromStdString(to_show));

    number = (int)(rand()%100);
    to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_2->setText(QString::fromStdString(to_show));

    number = (int)(rand()%100);
    to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_3->setText(QString::fromStdString(to_show));

    number = (int)(rand()%100);
    to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_4->setText(QString::fromStdString(to_show));

    number = (int)(rand()%100);
    to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_5->setText(QString::fromStdString(to_show));

    number = (int)(rand()%100);
    to_show = "";
    to_show+= (char)(number/10 + 48);
    to_show += (char)(number%10 + 48);
    this->possible_token += to_show;
    this->ui->token_6->setText(QString::fromStdString(to_show));
}


void generate_new_token::on_generate_button_2_clicked() {
    if (this->ui->password_line->text().toStdString() == this->user_data->password) {
        std::string to_send = "";
        to_send += ((char)GET_CHANGE_TOKEN);
        to_send += this->user_data->user;
        to_send += ",";
        to_send += this->ui->user_line->text().toStdString();
        to_send += ",";
        to_send += this->possible_token;
        to_send += ",";
        std::string result = "\0";
        result = this->local_client->send_and_receive(to_send);
        if (result[0] == '1') {
            QMessageBox::information(this, "Correcto", "El token ha sido actualizado");
        } else {
            QMessageBox::warning(this, "Error", "Usuario no existe");
        }
        this->possible_token = "";
        this->ui->user_line->setText(" ");
        this->ui->token_1->setText(" ");
        this->ui->token_2->setText(" ");
        this->ui->token_3->setText(" ");
        this->ui->token_4->setText(" ");
        this->ui->token_5->setText(" ");
        this->ui->token_6->setText(" ");
    } else {
        QMessageBox::warning(this, "Error", "Datos de confirmacion incorrectos");
        this->ui->password_line->setText("");
    }
}

