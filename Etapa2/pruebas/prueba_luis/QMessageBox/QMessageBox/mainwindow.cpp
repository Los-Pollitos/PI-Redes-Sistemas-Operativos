#include "mainwindow.h"
#include "ui_mainwindow.h"
// Used for push button
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

/*
  Types of messages:

  void about -> add a message
  void aboutQt -> shows everything about QT

  These return a StandardButton and have a fourth optional parameter
  StandardButton critical -> critical message with critical icon
  StandardButton information -> information message with icon
  StandardButton question -> question message with icon (yes or no)
  StandardButton warning -> warning message with icon
*/
void MainWindow::on_pushButton_clicked() {
    // Parent class, title, message
    // QMessageBox::about(this, "My Title", "This is my custom message");
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Title", "Want to quit?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        QApplication::quit();
    }
    /*
     qDebug can be used to print, it requires to be included
     qDebug() << "No is clicked";
    */
}


