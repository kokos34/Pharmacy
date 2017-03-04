#ifndef MEDICINESFORM_H
#define MEDICINESFORM_H

#include <QDialog>

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
};

#endif // MEDICINESFORM_H
