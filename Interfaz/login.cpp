#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login) {
    ui->setupUi(this);
    QPixmap pix ("../img/pollitos_incorporated_icon.png");
    this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
                                               ui->pic_label->height(),Qt::KeepAspectRatio));
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->tokenPage = new Token(nullptr);
    this->changePass = new change_password(this);
    this->setWindowTitle("Login");
    this->request_button = new logout_button("Logout");
    this->connect(this->request_button, &logout_button::pressed, this
                  , &login::generate_new);
}

login::~login() {
    delete this->ui;
    delete this->tokenPage;
    if (this->user_data) {
        delete this->user_data;
    }
    delete this->changePass;
    delete this->request_button;
}

void login::set_file_system(FS* file_system) {
    this->file_system = file_system;
}

bool login::validate_data(QString username, QString password) {
    bool answer = false;
    this->file_system->open(username.toStdString(), "Login.txt");
    if (this->file_system->is_open("Login.txt")) {
        this->file_system->reset_file_pointer(username.toStdString(), "Login.txt");
        bool found = false;
        std::string buffer = " ";

        // Find the username in the file
        while (!found && !this->file_system->is_eof(username.toStdString(), "Login.txt")) {
            buffer = this->file_system->read_until(username.toStdString(), "Login.txt", '\t');
            if (buffer != username.toStdString()) {
                // Read the rest of the data
                this->file_system->read_line(username.toStdString(), "Login.txt");
            } else {
                found = true;
            }
            buffer = " ";
        }
        // Compare
        if (found) {
            buffer = this->file_system->read_until(username.toStdString(), "Login.txt", '\t');
            if (buffer == password.toStdString()) {
                // The user was found and is inserted in the struct
                answer = true;
                this->user_data = new login_info();
                this->user_data->user = username.toStdString();
                this->user_data->password = password.toStdString();
                // Obtain the token
                for (int i = 0; i < TOKEN_SIZE; ++i) {
                    this->user_data->token[i] =
                        std::stoi(this->file_system->read_until(username.toStdString(), "Login.txt", ' '));
                }
            }
        }
        this->file_system->close(this->user_data->user, "Login.txt");
    }
    // Success
    return answer;
}

void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    if (this->validate_data(username, password)) {
        this->hide();
        this->tokenPage->setUserData(this->user_data);
        this->tokenPage->setParent_Button(this->request_button);
        this->tokenPage->show();
    } else {
       QMessageBox::warning(this, "Error", "Datos incorrectos");
       this->ui->user_input->setText("");
       this->ui->password_input->setText("");
    }
}

void login::on_forgot_button_clicked() {
    this->changePass->setModal(true);
    this->changePass->show();
}

void login::generate_new(){
    this->file_system->reset_file_pointer(user_data->user, "Login.txt");
    delete this->user_data;
    this->ui->user_input->setText("");
    this->ui->password_input->setText("");
    this->show();
}

