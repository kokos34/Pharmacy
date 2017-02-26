#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>

#include "pharmacieshandler.h"

namespace Ui {
class PharmaciesForm;
}

class PharmaciesForm : public QDialog
{
    Q_OBJECT

public:
    explicit PharmaciesForm(QWidget *parent = 0);
    ~PharmaciesForm();

private:
    Ui::PharmaciesForm *ui;
    bool isAndroid = true;
    void pushPharmaciesToTable();
};

#endif // PHARMACIESFORM_H
