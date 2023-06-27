#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->local_client = new client();
    this->login_page = new login();
    this->login_page->set_client(this->local_client);
    this->login_page->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (this->login_page) {
        delete this->login_page;
    }
    if (this->local_client) {
        delete this->local_client;
    }
}

