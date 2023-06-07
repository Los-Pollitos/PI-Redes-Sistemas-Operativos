#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->local_client = new client();
    this->loginPage = new login();
    this->loginPage->set_client(local_client);
    this->loginPage->show();
}

MainWindow::~MainWindow() {
    if (this->ui) {
     delete this->ui;
     this->ui = 0;
    }
    if (this->loginPage) {
        delete this->loginPage;
        this->loginPage = 0;
    }
    if (this->local_client) {
        delete this->local_client;
        this->local_client = 0;
    }
}
