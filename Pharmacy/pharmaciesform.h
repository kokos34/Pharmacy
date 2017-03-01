#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>
#include <QMessageBox>

#include "pharmacieshandler.h"
#include "pharmaciesmoreinfo.h"
#include "searchpharmacies.h"

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
    void receivePhraseAndMarkRows(vector<int>);

public slots:
    void on_pushButton_clicked();

private:
    Ui::PharmaciesForm *ui;
    SearchPharmacies* spDialog;
    bool isAndroid = true;
    void pushPharmaciesToTable();
    void prepareTableView();
};

#endif // PHARMACIESFORM_H
