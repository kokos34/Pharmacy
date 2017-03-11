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
    connect(ui->sortButton, SIGNAL(clicked()), this, SLOT(sortPharmacies()));
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

void PharmaciesForm::sortPharmacies()
{
    sortDialog = new SortPharmacies(this);
    sortDialog->show();

    if(sortDialog->exec() == QDialog::Accepted)
    {
        int sortByRow = sortDialog->getMarkedIndex();

        ui->tableWidget->sortByColumn(sortByRow);
    }
}

void PharmaciesForm::on_pushButton_2_clicked()
{

}

void PharmaciesForm::on_markOpen_clicked()
{
    QTime timeMeasurement = QTime::currentTime();
    int currentHour = timeMeasurement.hour();

    if(currentHour == 0)
        currentHour = 24;

    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString currentHours = ui->tableWidget->item(i, 2)->text();
        qDebug() << currentHours;

        QString openingHour = "";
        QString closingHour = "";
        int index = 0;

        QChar dash('-');

        while(currentHours.at(index)!=dash)
            openingHour.append(currentHours.at(index++));

        int indexOfDash = index+1;

        while(indexOfDash < currentHours.size())
            closingHour.append(currentHours.at(indexOfDash++));

        qDebug() << "opening " << openingHour << " closing " << closingHour;

        bool ok = false;

        int opening = openingHour.toInt(&ok, 10);
        int closing = closingHour.toInt(&ok, 10);

        if(ok)
        {
            if(currentHour >= opening && currentHour < closing)
                ui->tableWidget->selectRow(i);
        }
        else
            qDebug() << "Something went wrong with string-int conversion";
    }

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}
