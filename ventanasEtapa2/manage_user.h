#ifndef MANAGE_USER_H
#define MANAGE_USER_H

#include <QDialog>

namespace Ui {
class manage_user;
}

class manage_user : public QDialog
{
    Q_OBJECT

public:
    explicit manage_user(QWidget *parent = nullptr);
    ~manage_user();

private:
    Ui::manage_user *ui;
};

#endif // MANAGE_USER_H
