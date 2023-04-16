#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Set value to 0
    ui->progressBar->setValue(0);
    // Connects the horizontal slider, with the signal
    // value changed to the progress bar with the
    // slot set value
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
        ui->progressBar, SLOT(setValue(int)));
}

/*
  To remove the signal and slot you can also run disconnect
  disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
      ui->progressBar, SLOT(setValue(int)));
*/

MainWindow::~MainWindow() {
    delete ui;
}

