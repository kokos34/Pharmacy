#include "pharmaciesmoreinfo.h"
#include "ui_pharmaciesmoreinfo.h"

#include <QDebug>

PharmaciesMoreInfo::PharmaciesMoreInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PharmaciesMoreInfo)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("font-weight: bold; color: green");
}

PharmaciesMoreInfo::~PharmaciesMoreInfo()
{
    delete ui;
}

void PharmaciesMoreInfo::passIndex(int index)
{
    // Needed to show info about particular pharmacy, not all of them
    rowIndexFromParent = index;

    QString debugString = "index " + QString::number(rowIndexFromParent);
    qDebug() << debugString;
}

void PharmaciesMoreInfo::passListOfPharmacies(vector<vector<QString> > currList)
{
    listOfPharmacies = currList;
}

void PharmaciesMoreInfo::displayInfo()
{
    ui->tableWidget->insertRow(0);

    //0 - ph_name, 1 - ph_address, 2 - opening hours
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][0]));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][1]));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][2]));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][3]));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][4]));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(listOfPharmacies[rowIndexFromParent][5]));

    ui->tableWidget->itemAt(0, 5)->setToolTip(listOfPharmacies[rowIndexFromParent][5]);
}
