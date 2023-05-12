#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->file_system = new FS();
    this->load_file("../Archivos/Login.txt", "Login.txt");
    this->loginPage = new login(nullptr);
    this->loginPage->set_file_system(file_system);
    this->loginPage->show();
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->file_system;
}

void MainWindow::load_file(std::string location, std::string file_name) {

    // TODO(nosotros): borrar
    std::cout << "estoy en load file" << std::endl;


    std::ifstream file(location);
    std::string read_line = "";
    if (file.is_open()) {
        this->file_system->create(file_name);
        while (getline(file, read_line)) {
            read_line += '\n';

            // TODO(nosotros):
            std::cout << "voy a meter: " << read_line;

            this->file_system->append(file_name, read_line);
            read_line = "";
        }

        // TODO(nostros): borrar
        this->file_system->print_unit();

        file.close();
    }
}
