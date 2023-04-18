#ifndef HANDLE_REQUESTS_H
#define HANDLE_REQUESTS_H

#include <QDialog>
#include <QPushButton>
#include <vector>
#include <QVBoxLayout>

#include "description_button.h"
#include "request_description.h"

#define REQUEST_VACATIONS 1
#define PAYMENT_PROOF 2
#define WORK_PROOF 3
#define SALARY_PROOF 4

namespace Ui {
class handle_requests;
}

class handle_requests : public QDialog
{
    Q_OBJECT

public:
    explicit handle_requests(QWidget *parent = nullptr);
    void update_scroll();
    ~handle_requests();

private:
    QVBoxLayout * layout;
    Ui::handle_requests *ui;
    std::vector<description_button*> requests_buttons;
    request_description * description;

protected slots:
    void show_description(int id, int type);
};

#endif // HANDLE_REQUESTS_H
