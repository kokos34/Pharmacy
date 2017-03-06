#include "medicinesform.h"
#include "ui_medicinesform.h"

MedicinesForm::MedicinesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicinesForm)
{
    ui->setupUi(this);

    prepareTableView();
    pushMedicinesToTable();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(markPerscriptions()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(findClicked()));
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
