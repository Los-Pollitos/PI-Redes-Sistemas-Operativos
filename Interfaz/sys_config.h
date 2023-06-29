#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include <QDialog>

namespace Ui {
class sys_config;
}

class sys_config : public QDialog
{
    Q_OBJECT

public:
    explicit sys_config(QWidget *parent = nullptr);
    ~sys_config();

private:
    Ui::sys_config *ui;
};

#endif // SYS_CONFIG_H
