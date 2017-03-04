#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>

#include "pharmacieshandler.h"
#include "pharmaciesmoreinfo.h"
#include "searchpharmacies.h"
#include "sortpharmacies.h"

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

    void on_pushButton_2_clicked();

    void on_markOpen_clicked();

public slots:
    void on_pushButton_clicked();
    void sortPharmacies();

private:
    Ui::PharmaciesForm *ui;
    SearchPharmacies* spDialog;
    SortPharmacies* sortDialog;
    bool isAndroid = true;
    void pushPharmaciesToTable();
    void prepareTableView();
};

#endif // PHARMACIESFORM_H
