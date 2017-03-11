#ifndef MEDICINESFORM_H
#define MEDICINESFORM_H

#include <QDialog>

#include "medicineshandler.h"

namespace Ui {
class MedicinesForm;
}

class MedicinesForm : public QDialog
{
    Q_OBJECT

public:
    explicit MedicinesForm(QWidget *parent = 0);
    ~MedicinesForm();

private:
    Ui::MedicinesForm *ui;
    void pushMedicinesToTable();
    void prepareTableView();

private slots:
    void markPerscribed();
};

#endif // MEDICINESFORM_H
