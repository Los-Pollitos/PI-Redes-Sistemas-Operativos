#ifndef HUMAN_RESOURCES_H
#define HUMAN_RESOURCES_H

#include <QDialog>

#include "manage_user.h"

namespace Ui {
class human_resources;
}

class human_resources : public QDialog
{
    Q_OBJECT

public:
    explicit human_resources(QWidget *parent = nullptr);
    ~human_resources();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::human_resources *ui;
};

#endif // HUMAN_RESOURCES_H
