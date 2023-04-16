#ifndef TOKEN_H
#define TOKEN_H

#include <QDialog>
#include <QMessageBox>

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
    Ui::Token *ui;
};

#endif // TOKEN_H
