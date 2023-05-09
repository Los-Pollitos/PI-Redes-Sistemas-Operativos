#include "modify_user.h"
#include "ui_modify_user.h"
#include <fstream>

#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    modified_index = 0;
    ui->setupUi(this);
}

modify_user::~modify_user() {
    delete ui;
}

void modify_user::on_comboBox_activated(int index) {
    modified_index = index;
    // TODO(nosotros): rellenar info de usuarios con cantidad de usuarios real
    ui->employee_id->setReadOnly(true);
    ui->employee_id->setText(QString::number(this->ids[index]));
   //  ui->employee_job->setText(this->job[index]);
    ui->employee_salary->setText(QString::number(this->salary[index]));
    ui->employee_vacations->setText(QString::number(this->vacations[index]));
    ui->record->setPlainText(this->record[index]);
}

void modify_user::add_data() {
    // TODO(nosotros): leer de una base de datos
    // ui->comboBox->addItem("Empleado 1");
    // ui->comboBox->addItem("Empleado 2");

    // this->ids.append(12345678);
    // this->ids.append(87654321);

    // this->job.append("Trabajo1");
    // this->job.append("Trabajo2");

    // this->salary.append(123);
    // this->salary.append(321);

    // this->vacations.append(1);
    // this->vacations.append(2);

    // this->record.append(
    //     "Este expleado tiene muchas anotaciones. Anotación 1: llega tarde todos los lunes, parece que se duerme. Anotación 2: parece que tiene vida y se va temprano los viernes.");
    // this->record.append("Es un buen empleado, hace su trabajo.");

    // TODO(Angie): solo mostrarle la info al jefe directo
    // se debe leer el archivo
    std::ifstream data ("../Etapa 2/Archivos/Data.txt");
    // TODO(nosotros): try catch
    int i = 0;
    std::string temp = " ";
    if (data.is_open()) {
        while(data) {
            // users_data.append(user_data());
            // file >> users_data[i].user;
            // file >> temp;
            while (temp[0] < 48 && temp[0] > 58) {
                users_data[i].name.append(" ");
                users_data[i].name.append(temp);
                // file >> temp;
            }
            // va a salir con la identificacion
            users_data[i].identification = stoi(temp);
            // file >> users_data[i].salary;
            // file >> users_data[i].job;
            // file >> temp; // TODO(Angie). es el jefe
           //  file >> temp; // son las vacaciones asignadas
            //file >> users_data[i].available_vacations;
            ++i;
        }
        data.close();
    }

    
}

void modify_user::on_approve_changes_clicked() {
    QString password = ui->password->text();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox::information(this, "Correcto", "Cambios aplicados");
        this->update_data();
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

void modify_user::update_data() {
    // this->job[modified_index] = ui->employee_job->text();
    this->salary[modified_index] = ui->employee_salary->text().toInt();
    this->vacations[modified_index] = ui->employee_vacations->text().toInt();
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
    this->add_data();
}
