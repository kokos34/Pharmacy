#ifndef MEDICINESFORM_H
#define MEDICINESFORM_H

#include <QDialog>
#include <QMessageBox>

#include "medicineshandler.h"
#include "searchmedicines.h"

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

private slots:
    void markPerscriptions();

private:
    Ui::MedicinesForm *ui;
    SearchMedicines* searchDialog;
    void cleanSelection();
    void pushMedicinesToTable();
    void prepareTableView();
};

#endif // MEDICINESFORM_H
