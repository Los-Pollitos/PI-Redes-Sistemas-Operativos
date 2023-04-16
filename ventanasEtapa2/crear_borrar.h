#ifndef CREAR_BORRAR_H
#define CREAR_BORRAR_H

#include <QDialog>

namespace Ui {
class crear_borrar;
}

class crear_borrar : public QDialog
{
    Q_OBJECT

public:
    explicit crear_borrar(QWidget *parent = nullptr);
    ~crear_borrar();

private:
    Ui::crear_borrar *ui;
};

#endif // CREAR_BORRAR_H
