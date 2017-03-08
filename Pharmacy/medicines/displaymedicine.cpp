#include "displaymedicine.h"
#include "ui_displaymedicine.h"

DisplayMedicine::DisplayMedicine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayMedicine)
{
    ui->setupUi(this);
}

DisplayMedicine::~DisplayMedicine()
{
    delete ui;
}
