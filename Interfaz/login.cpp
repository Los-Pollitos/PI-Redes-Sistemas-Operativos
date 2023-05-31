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

void login::set_file_system(FS* file_system) {
    this->file_system = file_system;
}

void login::set_client(client* local_client){
    this->local_client = local_client;
    this->local_client->send_and_receive("0cjimenez,78e8ee0b2f67531b8eda7678fa42fb");
}

bool login::validate_data(QString username, QString password) {
    bool answer = false;
    this->file_system->open(username.toStdString(), "Login.txt");
    if (this->file_system->is_open("Login.txt")) {
        this->file_system->reset_file_pointer(username.toStdString(), "Login.txt");
        bool found = false;
        std::string buffer = " ";

        // Find the username in the file
        bool end_of_file = this->file_system->is_eof(username.toStdString(), "Login.txt");
        while (end_of_file == false && found == false) {
            buffer = this->file_system->read_until(username.toStdString(), "Login.txt", '\t');
            if (buffer != username.toStdString()) {
                // Read the rest of the data
                buffer = this->file_system->read_line(username.toStdString(), "Login.txt");
            } else {
                found = true;
            }
            buffer = " ";
            end_of_file = this->file_system->is_eof(username.toStdString(), "Login.txt");
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
        this->file_system->close(username.toStdString(), "Login.txt");
    }
    // Success
    return answer;
}

void login::on_login_button_clicked() {
    this->refresh_file_system();
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    if (this->validate_data(username, password)) {
        this->hide();
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
    // this->file_system->reset_file_pointer(user_data->user, "Login.txt");
    delete this->user_data;
    this->ui->user_input->setText("");
    this->ui->password_input->setText("");
    this->show();
}

void login::load_file(std::string location, std::string file_name) {
    std::ifstream file(location);
    std::string read_line = "";
    if (file.is_open()) {
       this->file_system->create(file_name);
       this->file_system->open("", file_name);
       if (this->file_system->is_open(file_name)) {
            while (getline(file, read_line)) {
                read_line += '\n';
                this->file_system->append(file_name, read_line);
                read_line = "";
            }
            this->file_system->close("", file_name);
       }
       file.close();
    }
}

void login::refresh_file_system() {
    if (this->file_system->open("", "Login.txt") != -1) {  // the file exists
       this->file_system->close("", "Login.txt");
       this->file_system->erase("Login.txt");
    }
    this->load_file("../Etapa2/Archivos/Login.txt", "Login.txt");
}
