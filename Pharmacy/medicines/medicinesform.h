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

private slots:
    void markPerscriptions();

private:
    Ui::MedicinesForm *ui;
    SearchMedicines* searchDialog;
    DisplayMedicine* medicineDialog;

    void cleanSelection();
    void pushMedicinesToTable();
    void prepareTableView();
};

#endif // MEDICINESFORM_H
