#ifndef HANDLE_REQUESTS_H
#define HANDLE_REQUESTS_H

#include <QDialog>
#include <QPushButton>
#include <vector>

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
    std::vector<QPushButton*> requests_buttons;

};

#endif // HANDLE_REQUESTS_H
