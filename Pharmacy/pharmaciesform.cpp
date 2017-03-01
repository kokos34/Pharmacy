#include "pharmaciesform.h"
#include "ui_pharmaciesform.h"

PharmaciesForm::PharmaciesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PharmaciesForm)
{
    ui->setupUi(this);

    prepareTableView();
    pushPharmaciesToTable();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
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

void PharmaciesForm::on_pushButton_clicked()
{
//    static int rowCounter = 0;

    spDialog = new SearchPharmacies(this);

    spDialog->show();

    if(spDialog->exec() == QDialog::Accepted)
    {
        vector<int> result = spDialog->findThePhrase();

        if(result.size() == 0)
        {
            QMessageBox::information(this, tr("Error"), tr("Cannot find the searched phrase"));
            return;
        }

//        if(rowCounter < result.size())
            ui->tableWidget->selectRow(result[0]);
        /*else
            rowCounter = 0;*/
    }
    delete spDialog;//->close();
}

void PharmaciesForm::receivePhraseAndMarkRows(vector<int> result)
{
    ui->tableWidget->selectRow(result[0]);
}
