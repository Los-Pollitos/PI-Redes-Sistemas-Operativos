#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login) {
    ui->setupUi(this);
    QPixmap pix (":/icons/pollitos_incorporated_icon.png");
    this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
                                               ui->pic_label->height(),Qt::KeepAspectRatio));
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->token_page = new Token(nullptr);
    this->change_pass = new change_password(this);
    this->setWindowTitle("Login");
    this->request_button = new logout_button("Logout");
    this->connect(this->request_button, &logout_button::pressed, this
                  , &login::generate_new);
}

login::~login() {
    if (this->ui) {
      delete this->ui;
      this->ui = 0;
    }
    if (this->change_pass) {
        delete this->change_pass;
        this->change_pass = 0;
    }
    if (this->request_button) {
       delete this->request_button;
       this->request_button = 0;
    }
    if (this->token_page) {
       delete this->token_page;
       this->token_page = 0;
    }
}

void login::set_client(client* local_client){
    this->local_client = local_client;
    // TODO (nosotros): borrar
    this->local_client->send_and_receive("Acjimenez,78e8ee0b2f67531b8eda7678fa42fb");
    this->local_client->send_and_receive("Ecjimenez,78e8ee0b2f67531b8eda7678fa42fb");
}

int login::validate_user(std::string username, std::string password) {
    std::string to_comunicate = "";
    std::cout << "GET_LOGIN es " << (char)GET_LOGIN << std::endl;
    to_comunicate += ((char)GET_LOGIN);
    to_comunicate += username;
    to_comunicate += ",";
    to_comunicate += password; // TODO (Emilia): Hash password
    std::string result = "\0";
    result = this->local_client->send_and_receive(to_comunicate);
    int to_return = ((int)result[0]) - 48;
    std::cout << "el usuario puede entrar? " << to_return << std::endl;
    return to_return;
}

void login::ask_for_token() {
    std::string to_send = "";
    to_send += ((char)GET_TOKEN);
    to_send += this->user_data->user;
    to_send += ",";
    std::string result = "\0";
    result = this->local_client->send_and_receive(to_send);
    if (result[0] != 'e') {
        int token_count = 0;
        for (int i = 0; i < TOKEN_SIZE*2; i+=2) {
           this->user_data->token[token_count] = (((int)result[i]) - 48)*10 +(((int)result[i+1]) - 48) ;
           ++token_count;
        }
    } else {
        std::cerr << "user does not exist or there was an error with comunication\n";
    }
}

void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    if (this->validate_user(username.toStdString(), password.toStdString()) == 1) {
        this->user_data = new login_info;
        this->user_data->user = username.toStdString();
        this->user_data->password = password.toStdString();

        this->ask_for_token();

        // TODO(emilia): Borrar comentarios de quemar token:
//        this->user_data->token[0] = 11;
//        this->user_data->token[1] = 12;
//        this->user_data->token[2] = 13;
//        this->user_data->token[3] = 21;
//        this->user_data->token[4] = 22;
//        this->user_data->token[5] = 23;

        this->hide();
        this->token_page->set_client(this->local_client);
        this->token_page->setUserData(this->user_data);
        this->token_page->setParent_Button(this->request_button);
        this->token_page->show();
    } else {
       QMessageBox::warning(this, "Error", "Datos incorrectos");
       this->ui->user_input->setText("");
       this->ui->password_input->setText("");
    }
}

void login::on_forgot_button_clicked() {
    this->change_pass->setModal(true);
    this->change_pass->show();
}

void login::generate_new(){
    delete this->user_data;
    this->ui->user_input->setText("");
    this->ui->password_input->setText("");
    this->show();
}

