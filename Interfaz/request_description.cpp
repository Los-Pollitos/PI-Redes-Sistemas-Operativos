#include "request_description.h"
#include "ui_request_description.h"

#include <QMessageBox>

QString request_description::request_type(int type) {
    QString string_type = "Solicitud de Vacaciones";
    switch (type) {
    case WORK_PROOF:
        string_type = "Constancia laboral";
        break;
    case SALARY_PROOF:
        string_type = "Constancia de salario";
        break;
    case PAYMENT_PROOF:
        string_type = "Comprobante de pago";
    }
    return string_type;
}

request_description::request_description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_description) {
    ui->setupUi(this);
    this->setWindowTitle("Descripción");
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->accept_label->setStyleSheet("color: #001f21;");
    this->ui->buttonBox->setStyleSheet("color: #001f21;");
    this->ui->file_button->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_descripcion->setStyleSheet("color: #001f21;");
    this->ui->label_fecha->setStyleSheet("color: #001f21;");
    this->ui->label_tipo->setStyleSheet("color: #001f21;");
    this->ui->lineEdit->setStyleSheet("color: #001f21;");
    this->ui->password_label->setStyleSheet("color: #001f21;");
}

void request_description::set_client(client* local_client){
    this->local_client = local_client;
}

void request_description::set_atributes(int day, int month, int year,
        int& type, QString user, QString& description,
        description_button*& parent_button, login_info* user_login,
        bool admin) {
    this->parent_button = parent_button;
    this->description = description;
    this->date[0]= day;
    this->date[1] = month;
    this->date[2] = year;
    this->type= type;
    this->admin = admin;
    this->user = user;
    this->description = description;

    int j = 0;

    std::string text = parent_button->text().toStdString();

    while (text[j] != ':') {
        ++j;
    }
    j += 2;


    if (!this->admin) {
       this->ui->buttonBox->hide();
       this->ui->password_label->hide();
       this->ui->lineEdit->hide();
       this->ui->accept_label->hide();
       if (this->type == REQUEST_VACATIONS_D || (this->type != REQUEST_VACATIONS_D && text[j] != 'A') ) {
           this->ui->file_button->hide();
       } else {
           this->ui->file_button->show();
       }
    } else {  // is admin
        this->ui->file_button->hide();
        this->ui->buttonBox->show();
        this->ui->password_label->show();
        this->ui->lineEdit->show();
        this->ui->accept_label->show();
    }

    QString date_string = QString::number(day);
    date_string += "/";
    date_string += QString::number(month);
    date_string += "/";
    date_string += QString::number(year);
    this->ui->label_descripcion->setPlainText(description);
    this->ui->label_descripcion->setReadOnly(true);
    this->ui->label_fecha->setText(date_string);
    this->ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->user_login = user_login;

    if (admin) {
        this->ui->label_tipo->setText(QString::fromStdString
                                      (this->parent_button->text().toStdString().substr(this->parent_button->text().toStdString().find(':')+2)));
    } else {
        this->ui->label_tipo->setText(QString::fromStdString
                                      (this->parent_button->text().toStdString().substr(0, this->parent_button->text().toStdString().find(':'))));
    }
}

request_description::~request_description() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void request_description::on_buttonBox_accepted() {
    QString password = this->ui->lineEdit->text();
    this->ui->lineEdit->clear();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Correcto");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Solicitud aceptada");
        show_message.exec();
        this->handle_request(ACCEPTED);
        this->parent_button->valid = false;
        this->close();
        emit this->parent_button->disapear(this->parent_button->identifier);
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
}

void request_description::on_buttonBox_rejected() {
    QString password = this->ui->lineEdit->text();
    this->ui->lineEdit->clear();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Correcto");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Solicitud denegada");
        show_message.exec();
        this->handle_request(DENIED);
        this->close();
        this->parent_button->valid = false;
        emit this->parent_button->disapear(this->parent_button->identifier);
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
}

void request_description::on_file_button_clicked() {
    std::string to_send = "";

    int j = 0;
    std::string text = parent_button->text().toStdString();

    while (text[j] != ':') {
        ++j;
    }
    j -= 2;


    switch (text[j]) {
    case 'g':
        to_send += ((char)ANSWER_PAYMENT_PROOF);
        break;
    case 'j':
        to_send += ((char)ANSWER_WORK_PROOF);
        break;
    case 'a':
        to_send += ((char)ANSWER_SALARY_PROOF);
        break;
    }
    to_send += std::to_string(parent_button->get_id_requests()) + ",";
    to_send = this->local_client->send_and_receive(to_send);

    switch (text[j]) {
    case 'g':
        this->generate_pay_PDF(to_send);
        break;
    case 'j':
        to_send += ((char)ANSWER_WORK_PROOF);
        break;
    case 'a':
        to_send += ((char)ANSWER_SALARY_PROOF);
        break;
    }
}

void request_description::generate_pdf(const QString& file_path, const QString& text, const QString& header, const QString& image_path, const QString& title) {
    QPdfWriter pdf_writer(file_path);
    pdf_writer.setPageSize(QPageSize(QPageSize::Letter));
    pdf_writer.setPageMargins(QMarginsF(30, 15, 30, 30));
    pdf_writer.setTitle(title);
    QPainter painter(&pdf_writer);
    painter.setFont(QFont("Times New Roman", 12));
    // Load the image
    QImage image(image_path);
    if (!image.isNull()) {
        // Scale the image to fit within the page width
        QImage scaled_image = image.scaledToWidth(pdf_writer.width() - 5000, Qt::SmoothTransformation);
        // Calculate the position to draw the image
        QRectF image_rect(pdf_writer.width() - 1500, pdf_writer.height() - 12000, scaled_image.width(), scaled_image.height());
        // Draw the image
        painter.drawImage(image_rect, scaled_image);
    } else {
        qDebug() << "Failed to load image";
    }
    // Draw the text
    painter.drawText(QRectF(15, 15, pdf_writer.width() - 60, pdf_writer.height() - 190), header);
    painter.setFont(QFont("Times New Roman", 24));
    painter.drawText(QRectF(pdf_writer.width() / 2 - 1500, pdf_writer.height() / 5, pdf_writer.width() - 60, pdf_writer.height() - 190), title);
    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(QRectF(15, pdf_writer.height() / 3, pdf_writer.width() - 60, pdf_writer.height() - 190), text);
    painter.end();
}


void request_description::handle_request(int solved) {
    std::time_t actual_time = std::time(nullptr);
    std::tm* now = std::localtime(&actual_time);

    int actual_day = now->tm_mday;
    int actual_month = now->tm_mon;
    int actual_year = now->tm_year + 1900;

    std::string to_send = "";
    to_send += ((char)PROCESS_REQUESTS);
    to_send += user_login->user + ",";
    to_send += std::to_string(parent_button->get_id_requests()) + ",";
    to_send += std::to_string(solved) + ",";
    to_send += std::to_string(actual_day) + ",";
    to_send += std::to_string(actual_month) + ",";
    to_send += std::to_string(actual_year) + '\0';


    this->local_client->send_and_receive(to_send);
}

void request_description::generate_pay_PDF(std::string result){
    std::string name = "";
    std::string user_id = "";
    std::string day = "";
    std::string month = "";
    std::string year = "";
    std::string pay_day = "";
    std::string signing = "";
    std::string salary = "";
    std::string deductibles = "";
    std::string job_title = "";
    std::string user_office = "";

    int temp = 0;

    for (size_t i = 0; i < result.length(); ++i){
        if (result[i] == ',') {
           ++temp;
        } else {
            switch (temp) {
            case 0:
                name += result[i];
                break;
            case 1:
                user_id += result[i];
                break;
            case 2:
                day += result[i];
                break;
            case 3:
                month += result[i];
                break;
            case 4:
                year += result[i];
                break;
            case 5:
                pay_day += result[i];
                break;
            case 6:
                signing += result[i];
                break;
            case 7:
                salary += result[i];
                break;
            case 8:
                deductibles += result[i];
                break;
            case 9:
                job_title += result[i];
                break;
            case 10:
                user_office += result[i];
                break;
           }
        }
    }

    int net_salary = stoi(salary) - stoi(deductibles);

    std::string title = "Constancia de pago";

    std::string header = "";
    std::string text = "";

    header += user_office + ", Costa Rica\n";
    header += day + " / " + month + " / " + year + "\n";
    header += "Los Pollitos Inc.";
    text += "Buenos días,\nPor este medio se hace constar el pago del empleado " + name + " con los siguientes datos:\n\n";
    text += "Nombre del empleado: " + name;
    text += "\nIdentificación del empleado: " + user_id;
    text += "\nPuesto en la empresa: " + job_title;
    text += "\nSucursal: " + user_office;
    text += "\nEl pago al empleado se realizó el día " + pay_day + "/" + month + "/" + year + " y este, contando un salario bruto de " + salary;
    text += " colones y unas deducciones de " + deductibles + " colones, terminó siendo de " + std::to_string(net_salary) + " colones.\n\n";
    text += "Atentamente,\n";
    text += signing;

    QString filePath = "../docs/output.pdf";
    QString imagePath = ":/icons/pollitos_incorporated_icon.png";

    this->generate_pdf(filePath, QString::fromStdString(text), QString::fromStdString(header), imagePath, QString::fromStdString(title));

}

void request_description::generate_work_PDF(std::string result) {

}

void request_description::generate_salary_PDF(std::string result) {

}

