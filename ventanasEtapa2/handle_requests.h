#ifndef HANDLE_REQUESTS_H
#define HANDLE_REQUESTS_H

#include <QDialog>
#include <QPushButton>
#include <vector>

#include "description_button.h"

namespace Ui {
class handle_requests;
}

class handle_requests : public QDialog
{
    Q_OBJECT

public:
    explicit handle_requests(QWidget *parent = nullptr);
    ~handle_requests();

private:
    Ui::handle_requests *ui;
    std::vector<description_button*> requests_buttons;

protected slots:
    void show_description(int id, int type);
};

#endif // HANDLE_REQUESTS_H
