#include "generate_new_token.h"
#include "ui_generate_new_token.h"
#include "security.h"

#include <QMessageBox>

/**
 * @brief Construct a new generate new token::generate new token object
 * 
 * @param parent Parent window
 */
generate_new_token::generate_new_token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generate_new_token)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->password_line->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Generar token nuevo");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->user_line->setStyleSheet("color: #001f21;");
    this->ui->password_line->setStyleSheet("color: #001f21;");
    this->ui->generate_button->setStyleSheet("color: #001f21;");
    this->ui->generate_button_2->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");

    this->ui->token_1->setEnabled(false);
    this->ui->token_1->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_2->setEnabled(false);
    this->ui->token_2->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_3->setEnabled(false);
    this->ui->token_3->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_4->setEnabled(false);
    this->ui->token_4->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_5->setEnabled(false);
    this->ui->token_5->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_6->setEnabled(false);
    this->ui->token_6->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->ui->token_1->setText(" ");
    this->ui->token_2->setText(" ");
    this->ui->token_3->setText(" ");
    this->ui->token_4->setText(" ");
    this->ui->token_5->setText(" ");
    this->ui->token_6->setText(" ");
}

/**
 * @brief Destroy the generate new token::generate new token object
 * 
 */
generate_new_token::~generate_new_token() {
    delete ui;
}

/**
 * @brief Receives user's login information and stores it
 * 
 * @param user_data User's login information
 */
void generate_new_token::set_login_info(login_info * user_data) {
    this->user_data = user_data;
}

/**
 * @brief Receives client from previous window and stores it
 * 
 * @param local_client Client receives from previous window
 */
void generate_new_token::set_client(client * local_client){
    this->local_client = local_client;
}

/**
 * @brief Indicates that new token must be generated and shown
 * 
 */
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


/**
 * @brief Indicates that boss wants to proceed with change of token
 * 
 */
void generate_new_token::on_generate_button_2_clicked() {
    if (this->ui->password_line->text().toStdString() == this->user_data->password) {
        std::string to_send = "";
        security security_manager;
        to_send += ((char)GET_CHANGE_TOKEN);
        to_send += this->user_data->user;
        to_send += ",";
        to_send += this->ui->user_line->text().toStdString();
        to_send += ",";
        std::string encrypted = security_manager.encrypt(this->possible_token);
        int i = 0;
        for (i = 0; i < 12; ++i) {
            to_send += std::to_string((int)encrypted[i]);
            to_send += ',';
        }
        to_send += '\0';
        std::string result = "\0";
        result = this->local_client->send_and_receive(to_send);
        if (result[0] == '1') {
            QMessageBox show_message =  QMessageBox();
            show_message.setWindowTitle("Información");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("El token ha sido actualizado");
            show_message.exec();
        } else {
            QMessageBox show_message =  QMessageBox();
            show_message.setWindowTitle("Error");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Datos de usuario incorrectos");
            show_message.exec();
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
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Datos de confirmación incorrectos");
        show_message.exec();
        this->ui->password_line->setText("");
    }
}

