#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

// para abrir una cuando cierro la segunda:
// https://forum.qt.io/topic/70354/open-new-qmainwindow-and-close-the-old-one-by-keeping-qapplication-alive/8

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix ("C:/Users/emili/Downloads/a.png");
    this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
                                              ui->pic_label->height(),Qt::KeepAspectRatio));
    this->label = new QLabel("Datos incorrectos", this);   // el label es de esta ventana
    this->label->setStyleSheet("color:red");  // color del texto
    this-> label->hide();  // inicia escondido
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->token = new Dialog(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete token;
}


void MainWindow::on_login_button_clicked() {
   QString username = ui->user_input->text();  // get username
   QString password = ui->password_input->text();
   this->label->hide();
   if (username == "yo" && password == "123") {
        // QMessageBox::information(this, "Bienvenido", "Datos correctos"); // alternativa al label
        hide();
        token->show();
   } else {
       this->label->resize(200, 200); // size of label
       this->label->setGeometry(QRect(95, 230, 100, 20)); // position of label
       this->label->show(); // se muestra label
   }
}

