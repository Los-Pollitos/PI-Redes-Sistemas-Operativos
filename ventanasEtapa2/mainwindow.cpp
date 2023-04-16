#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginPage = new login(this);
    loginPage->show();
    // this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

