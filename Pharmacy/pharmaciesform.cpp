#include "pharmaciesform.h"
#include "ui_pharmaciesform.h"

PharmaciesForm::PharmaciesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PharmaciesForm)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    pushPharmaciesToTable();
}

PharmaciesForm::~PharmaciesForm()
{
    delete ui;
}

void PharmaciesForm::pushPharmaciesToTable()
{
    vector<vector<QString>> listOfPharmacies = PharmaciesHandler::getListOfPharmacies();

    for(unsigned int row = 0; row < listOfPharmacies.size(); row++)
    {
        ui->tableWidget->insertRow(row);

        //0 - ph_name, 1 - ph_address, 2 - opening hours
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(listOfPharmacies[row][0]));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(listOfPharmacies[row][1]));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(listOfPharmacies[row][2]));
    }
}
