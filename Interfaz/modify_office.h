#ifndef MODIFY_OFFICE_H
#define MODIFY_OFFICE_H

#include <QDialog>

namespace Ui {
class modify_office;
}

class modify_office : public QDialog
{
    Q_OBJECT

public:
    explicit modify_office(QWidget *parent = nullptr);
    ~modify_office();

private:
    Ui::modify_office *ui;
};

#endif // MODIFY_OFFICE_H
