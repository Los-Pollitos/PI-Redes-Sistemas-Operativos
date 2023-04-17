#ifndef REQUEST_VACATIONS_H
#define REQUEST_VACATIONS_H

#include <QDialog>

namespace Ui {
class request_vacations;
}

class request_vacations : public QDialog
{
    Q_OBJECT

public:
    explicit request_vacations(QWidget *parent = nullptr);
    ~request_vacations();

private:
    Ui::request_vacations *ui;
};

#endif // REQUEST_VACATIONS_H
