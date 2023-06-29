#ifndef AUDITOR_H
#define AUDITOR_H

#include <QDialog>

namespace Ui {
class auditor;
}

class auditor : public QDialog
{
    Q_OBJECT

public:
    explicit auditor(QWidget *parent = nullptr);
    ~auditor();

private slots:
    void on_refresh_button_clicked();
    void on_search_button_clicked();

private:
    Ui::auditor *ui;
};

#endif // AUDITOR_H
