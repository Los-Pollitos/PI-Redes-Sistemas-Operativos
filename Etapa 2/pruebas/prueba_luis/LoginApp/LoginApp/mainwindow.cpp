#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Login_clicked() {
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username == "test" && password == "test") {
        QMessageBox::information(this, "Login", "Correct username and pasword");
        this->secDialog = new SecDialog(this);
        this->hide();
        secDialog->show();
    } else {
        QMessageBox::warning(this, "Login", "Incorrect username and pasword");
    }
}

