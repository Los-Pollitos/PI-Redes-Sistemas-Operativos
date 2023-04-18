#include "handle_requests.h"
#include "ui_handle_requests.h"
#include <QVBoxLayout>
#include <QPushButton>

handle_requests::handle_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::handle_requests)
{
    ui->setupUi(this);
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    auto * container = new QWidget();
    ui->scrollArea->setWidget( container );
    auto * layout = new QVBoxLayout(container);
    this->requests_buttons.push_back(new QPushButton( "1", container));
    this->requests_buttons.push_back(new QPushButton( "2", container));
    this->requests_buttons.push_back(new QPushButton( "3", container));
    this->requests_buttons.push_back(new QPushButton( "4", container));
    this->requests_buttons.push_back(new QPushButton( "5", container));
    this->requests_buttons.push_back(new QPushButton( "6", container));
    this->requests_buttons.push_back(new QPushButton( "7", container));
    this->requests_buttons.push_back(new QPushButton( "8", container));
    this->requests_buttons.push_back(new QPushButton( "9", container));
    layout->addWidget(this->requests_buttons[0]);
    layout->addWidget(this->requests_buttons[1]);
    layout->addWidget(this->requests_buttons[2]);
    layout->addWidget(this->requests_buttons[3]);
    layout->addWidget(this->requests_buttons[4]);
    layout->addWidget(this->requests_buttons[5]);
    layout->addWidget(this->requests_buttons[6]);
    layout->addWidget(this->requests_buttons[7]);
    layout->addWidget(this->requests_buttons[8]);


}

handle_requests::~handle_requests()
{
    delete ui;
}
