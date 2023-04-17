#ifndef TOKEN_H
#define TOKEN_H

#include <QDialog>
#include <QMessageBox>

#include "initial.h"

namespace Ui {
class Token;
}

class Token : public QDialog
{
    Q_OBJECT

public:
    explicit Token(QWidget *parent = nullptr);
    ~Token();

private slots:
    void on_validate_label_clicked();

private:
    Ui::Token* ui;
    initial* initial_page;
};

#endif // TOKEN_H
