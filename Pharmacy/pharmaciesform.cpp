#include "pharmaciesform.h"
#include "ui_pharmaciesform.h"

PharmaciesForm::PharmaciesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PharmaciesForm)
{
    ui->setupUi(this);

    prepareTableView();
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

void PharmaciesForm::prepareTableView()
{

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("font-weight: bold; color: green");

    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Address"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Opening hours"));

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PharmaciesForm::on_moreInfo_clicked()
{
    PharmaciesMoreInfo* infoProvider = new PharmaciesMoreInfo();
    infoProvider->setModal(true);
    infoProvider->passIndex(ui->tableWidget->selectionModel()->selectedRows().at(0).row());
    infoProvider->displayInfo();
    infoProvider->exec();
}
