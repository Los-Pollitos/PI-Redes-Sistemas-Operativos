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
    void add_data();

    void on_approve_changes_clicked();

private:
    Ui::modify_user *ui;
    QList<QString> names;
    QList<int> ids;
    QList<QString> job;
    QList<QString> subordinate;
    QList<int> salary;
    QList<int> vacations;
    // TODO(Angie): expediente
};

#endif // MODIFY_USER_H
