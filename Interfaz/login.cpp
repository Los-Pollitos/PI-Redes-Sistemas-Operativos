#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //QPixmap pix ("C:/Users/emili/Downloads/a.png");
    //this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
    //                                          ui->pic_label->height(),Qt::KeepAspectRatio));
    this->label = new QLabel("Datos incorrectos", this);   // el label es de esta ventana
    this->label->setStyleSheet("color:red");  // color del texto
    this-> label->hide();  // inicia escondido
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->tokenPage = new Token(this);
}

login::~login()
{
    delete ui;
    delete label;
    delete tokenPage;
}

void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    this->label->hide();
    if (username == "yo" && password == "123") {
        this->hide();
        this->tokenPage->show();
    } else {
        this->label->resize(200, 200); // size of label
        this->label->setGeometry(QRect(95, 230, 100, 20)); // position of label
        this->label->show(); // se muestra label
    }
}
