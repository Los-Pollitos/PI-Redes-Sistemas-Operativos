#ifndef REQUEST_DESCRIPTION_H
#define REQUEST_DESCRIPTION_H

#include <QDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QImage>

#include "description_button.h"
#include "login_info.h"
#include "client.h"

#define REQUEST_VACATIONS_D 0
#define PROOF_D 1


namespace Ui {
class request_description;
}

class request_description : public QDialog
{
    Q_OBJECT

public:
    request_description();
    explicit request_description(QWidget *parent = nullptr);
    void set_atributes(int day, int month, int year, int& type, QString user, QString& description, description_button *& parent_button, login_info * user_login, bool admin);
    ~request_description();
    void set_client (client * local_client);
    void handle_request(int solved);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_file_button_clicked();

private:
    // Attributes
    Ui::request_description *ui;
    int date[3];
    int type;
    bool admin;
    description_button * parent_button;
    QString user;
    QString description;
    login_info * user_login;
    client* local_client;

    // Private method
    void generate_pdf(const QString& file_path, const QString& text, const QString& header, const QString& image_path, const QString& title);
    QString request_type(int type);
    void generate_pay_PDF(std::string result);
    void generate_work_PDF(std::string result);
    void generate_salary_PDF(std::string result);
};

#endif // REQUEST_DESCRIPTION_H
