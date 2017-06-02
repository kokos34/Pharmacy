#include "medicinesform.h"
#include "ui_medicinesform.h"

using namespace::std;

MedicinesForm::MedicinesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicinesForm)
{
    ui->setupUi(this);

    prepareTableView();
    pushMedicinesToTable();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(markPerscriptions()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(ui->displayImage, SIGNAL(clicked()), this, SLOT(displayImage()));
    connect(ui->sortButton, SIGNAL(clicked()), this, SLOT(sort()));
    connect(ui->showPerscription, SIGNAL(clicked()), this, SLOT(showPerscription()));
    connect(ui->addMedicine, SIGNAL(clicked()), this, SLOT(addMedicine()));
}

MedicinesForm::~MedicinesForm()
{
    delete ui;
}

void MedicinesForm::pushMedicinesToTable()
{
    listOfMedicines = MedicinesHandler::getListOfMedicines();

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

void MedicinesForm::markPerscriptions()
{
    cleanSelection();

    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    int rows = ui->tableWidget->rowCount();
    const int perscColumn = 2;

    for(int i = 0; i < rows; i++)
    {
        int compare = 1;
        if(( compare = QString::compare(ui->tableWidget->item(i, perscColumn)->text(), "yes", Qt::CaseInsensitive)) == 0)
            ui->tableWidget->selectRow(i);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MedicinesForm::findClicked()
{
    searchDialog = new SearchMedicines(this);

    searchDialog->show();

    int searchByColumn;
    QString phrase;

    cleanSelection();

    if(searchDialog->exec() == QDialog::Accepted)
    {
        QMap<QString, int> result = searchDialog->getResultMap();

        searchByColumn = result.values().at(0);

        //Since we do not search by each row we need to omit the 2 rows between
        // name and note
        if(searchByColumn == 1)
            searchByColumn = 3;

        phrase = result.keys().at(0);

        ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        bool phraseFound = false;

        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            if(ui->tableWidget->item(i, searchByColumn)->text() == phrase)
            {
                phraseFound = true;
                ui->tableWidget->selectRow(i);
            }
        }

        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        if(!phraseFound)
            QMessageBox::information(this, tr("Note"), tr("No phrase found matching criteria") );
    }

    delete searchDialog;
}

void MedicinesForm::sort()
{
    sortDialog = new SortMedicines(this);
    sortDialog->show();

    if(sortDialog->exec() == QDialog::Accepted)
    {
        indexToSortBy = sortDialog->getMarkedIndex();
        ui->tableWidget->sortByColumn(indexToSortBy, Qt::AscendingOrder);

        std::sort(listOfMedicines.begin(),
                listOfMedicines.end(),
                MedicinesForm::compareVectors);
    }

    delete sortDialog;
}

bool MedicinesForm::compareVectors(vector<QString> a, vector<QString> b)
{
    int resultOfComparison = QString::compare(a[0], b[0], Qt::CaseInsensitive);

    if(resultOfComparison < 0)
        return true;
    else
        return false;
}

void MedicinesForm::cleanSelection()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QModelIndex id = ui->tableWidget->model()->index(i, j, QModelIndex());
            ui->tableWidget->selectionModel()->select(id, QItemSelectionModel::Deselect);
        }
    }
}

void MedicinesForm::displayImage()
{
    if(!ui->tableWidget->selectionModel()->hasSelection())
        return;

    int markedPharmacyRowIndex = ui->tableWidget->selectionModel()->selectedRows().at(0).row();
    QString markedPharmacyName = ui->tableWidget->item(markedPharmacyRowIndex, 0)->text();

    QByteArray* arrayPicture = MedicinesHandler::getMedicinePicture(markedPharmacyName);

    if(arrayPicture->isEmpty())
        qDebug() << "empty pixmap";

    QPixmap pixmap = QPixmap();//":/new/prefix1/no_picture.png");

    pixmap.loadFromData(*arrayPicture);

    medicineDialog = new DisplayMedicine(this);

    medicineDialog->passPixmapToDisplay(pixmap);

    medicineDialog->setModal(true);
    medicineDialog->exec();

    delete medicineDialog;
}

void MedicinesForm::showPerscription()
{
    if(!ui->tableWidget->currentIndex().isValid())
        QMessageBox::information(this, tr("Error"), tr("Row was not selected!") );

    int selectedRow = ui->tableWidget->selectionModel()->currentIndex().row();

    QString name = ui->tableWidget->item(selectedRow, 0)->text();

    qDebug() << "medname = " << name;

    receiptDisplayer = new ShowReceipt(this);
    receiptDisplayer->show();

    receiptDisplayer->getMedicineName(name);
    receiptDisplayer->showReceiptFile();
}

void MedicinesForm::addMedicine()
{
    addMedicineDialog = new AddMedicine(this);
    addMedicineDialog->show();

    if(addMedicineDialog->exec() == QDialog::Accepted)
    {
        MedicinesHandler::refreshMedicines();

        while (ui->tableWidget->rowCount() > 0)
        {
            ui->tableWidget->removeRow(0);
        }

        pushMedicinesToTable();
    }

    delete addMedicineDialog;
}
