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
    auto * button1 = new QPushButton( "1", container);
    auto * button2 = new QPushButton( "2", container);
    auto * button3 = new QPushButton( "3", container);
    auto * button4 = new QPushButton( "4", container);
    auto * button5 = new QPushButton( "5", container);
    auto * button6 = new QPushButton( "6", container);
    auto * button7 = new QPushButton( "7", container);
    auto * button8 = new QPushButton( "8", container);
    auto * button9 = new QPushButton( "9", container);
    layout->addWidget( button1 );
    layout->addWidget( button2 );
    layout->addWidget( button3 );
    layout->addWidget( button4 );
    layout->addWidget( button5 );
    layout->addWidget( button6 );
    layout->addWidget( button7 );
    layout->addWidget( button8 );
    layout->addWidget( button9 );


}

handle_requests::~handle_requests()
{
    delete ui;
}
