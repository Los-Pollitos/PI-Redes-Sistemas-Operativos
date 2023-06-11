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
       this->ui->file_button->setText("Descargar archivo");
       this->ui->buttonBox->hide();
       this->ui->password_label->hide();
       this->ui->lineEdit->hide();
       this->ui->accept_label->hide();
       if (this->type == REQUEST_VACATIONS_D || text[j] != 'A') {
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
    QString type_string = this->request_type(this->type);
    this->ui->label_tipo->setText(type_string);
    this->ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->user_login = user_login;
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

    switch (this->type) {
    case 0:
        to_send += ((char)ANSWER_PAYMENT_PROOF);
        break;
    case 1:
        to_send += ((char)ANSWER_WORK_PROOF);
        break;
    case 2:
        to_send += ((char)ANSWER_SALARY_PROOF);
        break;
    }
    to_send += std::to_string(parent_button->get_id_requests());
    to_send = this->local_client->send_and_receive(to_send);
}

void request_description::generate_pdf(const QString& file_path, const QString& text, const QString& image_path) {
    QPdfWriter pdf_writer(file_path);
    pdf_writer.setPageSize(QPageSize(QPageSize::Letter));
    pdf_writer.setPageMargins(QMarginsF(15, 15, 30, 30));
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
    painter.drawText(QRectF(15, 15, pdf_writer.width() - 60, pdf_writer.height() - 190), text);
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

