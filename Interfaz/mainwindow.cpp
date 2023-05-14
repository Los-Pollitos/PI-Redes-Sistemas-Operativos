#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->file_system = new FS();
    this->load_file("../Etapa2/Archivos/Login.txt", "Login.txt");
    this->loginPage = new login(nullptr);
    this->loginPage->set_file_system(file_system);
    this->loginPage->show();
}

MainWindow::~MainWindow() {
    delete this->loginPage;
    delete this->ui;
    delete this->file_system;
}

void MainWindow::load_file(std::string location, std::string file_name) {
    std::ifstream file(location);
    std::string read_line = "";
    if (file.is_open()) {
        this->file_system->create(file_name);
        this->file_system->open("", file_name);
        if (this->file_system->is_open(file_name)) {
            while (getline(file, read_line)) {
                read_line += '\n';
                this->file_system->append(file_name, read_line);
                read_line = "";
            }
            this->file_system->close("", file_name);
        }
        file.close();
    }
}
