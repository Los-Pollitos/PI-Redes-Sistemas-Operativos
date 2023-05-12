#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loginPage = new login(nullptr);
    this->loginPage->show();

    this->file_system = new FS();
    this->load_file("../Archivos/login.txt", "login.txt");

    // this->hide();
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->file_system;
}

void MainWindow::load_file(std::string location, std::string file_name) {
    std::ifstream file(location);
    std::string read_line = "";
    if (file.is_open()) {
        this->file_system->create(file_name);
        while (getline(file, read_line)) {
            read_line += '\n';
            this->file_system->append(file_name, read_line);
            read_line = "";
        }

        this->file_system->print_unit();

        file.close();
    }
}
