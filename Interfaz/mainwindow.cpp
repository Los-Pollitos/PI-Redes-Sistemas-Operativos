#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->file_system = new FS();
    this->local_client = new client();
    this->loginPage = new login();
    this->loginPage->set_file_system(file_system);
    this->loginPage->set_client(local_client);
    this->loginPage->show();
}

MainWindow::~MainWindow() {
    if (this->ui) {
     delete this->ui;
     this->ui = 0;
    }
    if (this->file_system) {
        delete this->file_system;
        this->file_system = 0;
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
