#ifndef CONSULT_REQUESTS_H
#define CONSULT_REQUESTS_H

#include <QDialog>

namespace Ui {
class consult_requests;
}

class consult_requests : public QDialog
{
    Q_OBJECT

public:
    explicit consult_requests(QWidget *parent = nullptr);
    ~consult_requests();

private:
    Ui::consult_requests *ui;
};

#endif // CONSULT_REQUESTS_H
