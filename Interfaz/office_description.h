#ifndef OFFICE_DESCRIPTION_H
#define OFFICE_DESCRIPTION_H

#include <QDialog>

namespace Ui {
class office_description;
}

class office_description : public QDialog
{
    Q_OBJECT

public:
    explicit office_description(QWidget *parent = nullptr);
    ~office_description();

private:
    Ui::office_description *ui;
};

#endif // OFFICE_DESCRIPTION_H
