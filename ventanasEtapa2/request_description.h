#ifndef REQUEST_DESCRIPTION_H
#define REQUEST_DESCRIPTION_H

#include <QDialog>

namespace Ui {
class request_description;
}

class request_description : public QDialog
{
    Q_OBJECT

public:
    explicit request_description(QWidget *parent = nullptr);
    ~request_description();

private:
    Ui::request_description *ui;
};

#endif // REQUEST_DESCRIPTION_H
