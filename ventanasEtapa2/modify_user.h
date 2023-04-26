#ifndef MODIFY_USER_H
#define MODIFY_USER_H

#include <QDialog>

namespace Ui {
class modify_user;
}

class modify_user : public QDialog
{
    Q_OBJECT

public:
    explicit modify_user(QWidget *parent = nullptr);
    ~modify_user();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::modify_user *ui;
};

#endif // MODIFY_USER_H
