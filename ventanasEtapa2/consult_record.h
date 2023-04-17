#ifndef CONSULT_RECORD_H
#define CONSULT_RECORD_H

#include <QDialog>

namespace Ui {
class consult_record;
}

class consult_record : public QDialog
{
    Q_OBJECT

public:
    explicit consult_record(QWidget *parent = nullptr);
    ~consult_record();

private:
    Ui::consult_record *ui;
};

#endif // CONSULT_RECORD_H
