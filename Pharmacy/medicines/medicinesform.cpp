#include "medicinesform.h"
#include "ui_medicinesform.h"

MedicinesForm::MedicinesForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicinesForm)
{
    ui->setupUi(this);
}

MedicinesForm::~MedicinesForm()
{
    delete ui;
}
