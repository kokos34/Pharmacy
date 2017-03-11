#include "medicinesform.h"
#include "ui_medicinesform.h"

MedicinesForm::MedicinesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicinesForm)
{
    ui->setupUi(this);

    prepareTableView();
    pushMedicinesToTable();

    connect(ui->perscribed, SIGNAL(clicked()), this, SLOT(markPerscribed()));
}

MedicinesForm::~MedicinesForm()
{
    delete ui;
}

void MedicinesForm::pushMedicinesToTable()
{
    vector<vector<QString>> listOfMedicines = MedicinesHandler::getListOfMedicines();

    for(unsigned int row = 0; row < listOfMedicines.size(); row++)
    {
        ui->tableWidget->insertRow(row);

        //0 - med_name, 1 - med_quantity, etc
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(listOfMedicines[row][0]));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(listOfMedicines[row][1]));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(listOfMedicines[row][2]));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(listOfMedicines[row][3]));
    }
}

void MedicinesForm::prepareTableView()
{

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("font-weight: bold; color: green");

    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MedicinesForm::markPerscribed()
{
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString currentItem = ui->tableWidget->item(i, 2)->text();
        int compare = 1;

        if((compare = QString::compare(currentItem, "yes", Qt::CaseInsensitive)) == 0)
            ui->tableWidget->selectRow(i);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

}
