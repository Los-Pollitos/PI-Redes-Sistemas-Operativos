#include "login.h"
#include "ui_login.h"
#include "security.h"
#include <QMessageBox>

/**
 * @brief Construct a new login::login object
 *
 * @param parent Parent window
 */
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login) {
    ui->setupUi(this);
    QPixmap pix (":/icons/pollitos_incorporated_icon.png");
    this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
                                              ui->pic_label->height(),Qt::KeepAspectRatio));
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->setStyleSheet("background-color: #ECEAE5;");
    ui->password_label->setStyleSheet("color: #001f21;");
    ui->user_label->setStyleSheet("color: #001f21;");
    ui->password_input->setStyleSheet("color: #001f21;");
    ui->user_input->setStyleSheet("color: #001f21;");
    ui->label->setStyleSheet("color: #001f21;");
    ui->login_button->setStyleSheet("color: #001f21;");
    this->token_page = new Token(nullptr);
    this->setWindowTitle("Login");
    this->request_button = new logout_button("Logout");
    this->connect(this->request_button, &logout_button::pressed, this
                  , &login::generate_new);
}

/**
 * @brief Destroy the login::login object
 *
 */
login::~login() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
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

/**
 * @brief Receives and stores a client
 *
 * @param local_client Client that will be stored
 */
void login::set_client(client* local_client){
    this->local_client = local_client;
}

/**
 * @brief Asks client to indicate if user is valid
 *
 * @param username Username to check if it is valid
 * @param password Password to check if it is valid for the user
 * @return int 1 if it is correct, 0 if it is not
 */
int login::validate_user(std::string username, std::string password) {
    std::string to_comunicate = "";
    security security_manager;
    to_comunicate += ((char)LOGIN);
    to_comunicate += username;
    to_comunicate += ",";
    to_comunicate += security_manager.hash_string(password);
    std::string result = "\0";
    result = this->local_client->send_and_receive(to_comunicate);
    int to_return = ((int)result[0]) - 48;
    return to_return;
}

/**
 * @brief Asks client to send token information in order to verify if the user
 * has their token
 *
 */
void login::ask_for_token() {
    std::string to_send = "";
    to_send += ((char)TOKEN);
    to_send += this->user_data->user;
    to_send += ",";
    std::string result = "\0";
    result = this->local_client->send_and_receive(to_send);
    security security_manager;
    std::string adapted_result= "";
    int i = 0;
    for (int j = 0; j < 12; ++j) {
        if (result[i+1] == ',') {
            adapted_result += (char)(result[i]-48);
        } else if (result[i+2] == ','){
            adapted_result += (char)(((int)result[i]) - 48)*10 +(((int)result[i+1]) - 48);
            ++i; // ignore i+1
        } else {
            adapted_result += (char)(((int)result[i] - 48)*100 + ((int)result[i+1] -48)*10 - +(((int)result[i+2] -48)));
            i+=2; // ignore i+2
        }
        // next one would be a ,
        i+=2;
    }
    result = security_manager.decrypt(adapted_result);
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

/**
 * @brief asks client for user's role
 * @return role
 */
int login::ask_for_role() {
    char result = '0';
    std::string to_send = "";
    to_send += (char(GET_ROLES));
    to_send += this->user_data->user;
    to_send += ",";
    std::string from_server = "";
    from_server += this->local_client->send_and_receive(to_send);
    int correct = (int)(from_server[0]-48);
    result = from_server[1];
    this->user_data->roles = result;
    return correct;
}

/**
 * @brief Indicates that user must be validated
 *
 */
void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    if (this->validate_user(username.toStdString(), password.toStdString()) == 1) {
        this->user_data = new login_info;
        this->user_data->user = username.toStdString();
        this->user_data->password = password.toStdString();
        this->ask_for_token();
        if (this->ask_for_role() == 1 && ((this->user_data->roles & AUDITOR) == AUDITOR)) {
            this->hide();
            this->token_page->set_client(this->local_client);
            this->token_page->setUserData(this->user_data);
            this->token_page->setParent_Button(this->request_button);
            this->token_page->show();
        } else {
            QMessageBox show_wrong_role =  QMessageBox();
            show_wrong_role.setWindowTitle("Error");
            show_wrong_role.setModal(true);
            show_wrong_role.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_wrong_role.setText("Datos incorrectos");
            show_wrong_role.exec();
            this->ui->user_input->setText("");
            this->ui->password_input->setText("");
        }
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Datos incorrectos");
        show_message.exec();
        this->ui->user_input->setText("");
        this->ui->password_input->setText("");
    }
}


/**
 * @brief Resets login window
 *
 */
void login::generate_new(){
    delete this->user_data;
    this->ui->user_input->setText("");
    this->ui->password_input->setText("");
    this->show();
}
