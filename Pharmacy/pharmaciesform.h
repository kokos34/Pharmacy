#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>

#include "pharmacieshandler.h"
#include "pharmaciesmoreinfo.h"

namespace Ui {
class PharmaciesForm;
}

class PharmaciesForm : public QDialog
{
    Q_OBJECT

public:
    explicit PharmaciesForm(QWidget *parent = 0);
    ~PharmaciesForm();

private slots:
    void on_moreInfo_clicked();

private:
    Ui::PharmaciesForm *ui;
    bool isAndroid = true;
    void pushPharmaciesToTable();
    void prepareTableView();
};

#endif // PHARMACIESFORM_H
