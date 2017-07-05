#ifndef MEDICINESFORM_H
#define MEDICINESFORM_H

#include <QDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include "medicineshandler.h"
#include "searchmedicines.h"
#include "displaymedicine.h"
#include "sortmedicines.h"
#include "showreceipt.h"
#include "addmedicine.h"

#include <algorithm>

namespace Ui {
class MedicinesForm;
}

class MedicinesForm : public QDialog
{
    Q_OBJECT

public:
    explicit MedicinesForm(QWidget *parent = 0);
    ~MedicinesForm();

public slots:
    void findClicked();
    void displayImage();
    void sort();
    void showPerscription();
    void addMedicine();

private slots:
    void markPerscriptions();

private:
    Ui::MedicinesForm *ui;
    SearchMedicines* searchDialog;
    DisplayMedicine* medicineDialog;
    SortMedicines* sortDialog;
    ShowReceipt* receiptDisplayer;
    AddMedicine* addMedicineDialog;

    vector<vector<QString>> listOfMedicines;
    static bool compareVectors(vector<QString>, vector<QString>);

    void cleanSelection();
    void pushMedicinesToTable();
    void prepareTableView();

    int indexToSortBy;
};

#endif // MEDICINESFORM_H
