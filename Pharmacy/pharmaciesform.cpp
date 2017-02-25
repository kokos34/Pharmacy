#include "pharmaciesform.h"
#include "ui_pharmaciesform.h"

PharmaciesForm::PharmaciesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PharmaciesForm)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

PharmaciesForm::~PharmaciesForm()
{
    delete ui;
}
