#include "consult_record.h"
#include "ui_consult_record.h"

consult_record::consult_record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_record)
{
    ui->setupUi(this);
}

consult_record::~consult_record()
{
    delete ui;
}
