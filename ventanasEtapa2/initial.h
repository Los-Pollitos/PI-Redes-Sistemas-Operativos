#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>

namespace Ui {
class initial;
}

class initial : public QDialog
{
    Q_OBJECT

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();

private:
    Ui::initial *ui;
};

#endif // INITIAL_H
