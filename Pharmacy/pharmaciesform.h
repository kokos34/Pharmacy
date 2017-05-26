#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>

#include "pharmacieshandler.h"
#include "pharmaciesmoreinfo.h"
#include "searchpharmacies.h"
#include "sortpharmacies.h"
#include "addpharmacyform.h"
#include "deletepharmacy.h"

#include <algorithm>

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
    void deletePharmacies();

public slots:
    void on_pushButton_clicked();
    void sortPharmacies();
    void addPharmacy();

private:
    Ui::PharmaciesForm *ui;
    SearchPharmacies* spDialog;
    SortPharmacies* sortDialog;
    AddPharmacyForm* addDialog;

    bool isAndroid = true;
    QItemSelectionModel* selectedRows;
    vector<vector<QString>> listOfPharmacies;

    void pushPharmaciesToTable();
    void prepareTableView();
    void refreshTableIndexes();
    static bool compareVectors(vector<QString>, vector<QString>);
    int columnSorter;
};

#endif // PHARMACIESFORM_H
