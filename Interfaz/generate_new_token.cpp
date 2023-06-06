#include "generate_new_token.h"
#include "ui_generate_new_token.h"

generate_new_token::generate_new_token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generate_new_token)
{
    ui->setupUi(this);
    this->setWindowTitle("Generar token nuevo");
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

}

