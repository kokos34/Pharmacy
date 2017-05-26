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
    connect(ui->addPharmacyButton, SIGNAL(clicked()), this, SLOT(addPharmacy()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deletePharmacies()));
}

PharmaciesForm::~PharmaciesForm()
{
//    delete selectedRows;
    delete ui;
}

void PharmaciesForm::pushPharmaciesToTable()
{
    listOfPharmacies = PharmaciesHandler::getListOfPharmacies();

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
    selectedRows = ui->tableWidget->selectionModel();

    if(!selectedRows->hasSelection())
    {
        QMessageBox::information(this, tr("Error"), tr("No rows are selected!"));
        return;
    }

    infoProvider->passListOfPharmacies(listOfPharmacies);

    infoProvider->setModal(true);
    infoProvider->passIndex(ui->tableWidget->selectionModel()->selectedRows().at(0).row());
    infoProvider->displayInfo();
    infoProvider->exec();

    // This might cause a problem!

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PharmaciesForm::on_pushButton_clicked()
{
    spDialog = new SearchPharmacies(this);

    spDialog->show();

    spDialog->getListOfPharmacies(listOfPharmacies);

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
    delete spDialog;
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
        columnSorter = sortByRow;

        ui->tableWidget->sortByColumn(sortByRow, Qt::AscendingOrder);
        sort(listOfPharmacies.begin(),
             listOfPharmacies.end(),
             PharmaciesForm::compareVectors);
    }

    delete sortDialog;
}

bool PharmaciesForm::compareVectors(vector<QString> a, vector<QString> b)
{
    int resultOfComparison = QString::compare(a[0], b[0], Qt::CaseInsensitive);

    if(resultOfComparison < 0)
        return true;
    else
        return false;
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

void PharmaciesForm::addPharmacy()
{
    addDialog = new AddPharmacyForm(this);
    addDialog->show();

    if(addDialog->exec() == QDialog::Accepted)
    {
        PharmaciesHandler::refreshPharmacies();

        while (ui->tableWidget->rowCount() > 0)
        {
            ui->tableWidget->removeRow(0);
        }

        pushPharmaciesToTable();
    }

    delete addDialog;
}

void PharmaciesForm::deletePharmacies()
{
    const int row = ui->tableWidget->selectionModel()->selectedRows().at(0).row();
    QString name = ui->tableWidget->item(row, 0)->text();

    DeletePharmacy pharmacyDeleter(name);
    bool success = pharmacyDeleter.updateFile();

    if(success)
    {
        PharmaciesHandler::refreshPharmacies();

        while (ui->tableWidget->rowCount() > 0)
        {
            ui->tableWidget->removeRow(0);
        }

        pushPharmaciesToTable();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), tr("Could not find or remove the row!"));
        return;
    }
}
