#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

namespace Ui {
class manager;
}

class manager : public QDialog
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

private:
    Ui::manager *ui;
};

#endif // MANAGER_H
