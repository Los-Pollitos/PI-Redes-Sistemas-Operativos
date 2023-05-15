#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->file_system = new FS();
    this->loginPage = new login();
    this->loginPage->set_file_system(file_system);
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
}
