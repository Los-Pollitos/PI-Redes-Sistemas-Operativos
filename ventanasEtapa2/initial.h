#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>
#include "human_resources.h"
#include "manager.h"

namespace Ui {
class initial;
}

class initial : public QDialog
{
    Q_OBJECT

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();

private slots:
    void on_funciones_especiales_clicked();

private:
    Ui::initial *ui;
    human_resources * hhrr;
    manager * office_manager;
};

#endif // INITIAL_H
