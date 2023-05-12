#ifndef INICIAL_H
#define INICIAL_H

#include <QDialog>

namespace Ui {
class inicial;
}

class inicial : public QDialog
{
    Q_OBJECT

public:
    explicit inicial(QWidget *parent = nullptr);
    ~inicial();

private:
    Ui::inicial *ui;
};

#endif // INICIAL_H
