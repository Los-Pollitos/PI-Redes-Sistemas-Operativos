#ifndef AUDITOR_H
#define AUDITOR_H

#include <QDialog>
#include "logout_button.h"

namespace Ui {
class auditor;
}

class auditor : public QDialog
{
    Q_OBJECT

public:
    explicit auditor(QWidget *parent = nullptr);
    ~auditor();
    void set_logout_button(logout_button * parent_button);

private slots:
    void on_refresh_button_clicked();
    void on_search_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::auditor *ui;
    logout_button * exit_page;
};

#endif // AUDITOR_H
