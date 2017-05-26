#ifndef PHARMACIESMOREINFO_H
#define PHARMACIESMOREINFO_H

#include <QDialog>

#include <vector>

#include "pharmacieshandler.h"

namespace Ui {
class PharmaciesMoreInfo;
}

class PharmaciesMoreInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PharmaciesMoreInfo(QWidget *parent = 0);
    ~PharmaciesMoreInfo();
    void passIndex(int index);
    void displayInfo();
    void passListOfPharmacies(vector<vector<QString>>);

private:
    Ui::PharmaciesMoreInfo *ui;
    int rowIndexFromParent;
    vector<vector<QString>> listOfPharmacies;
};

#endif // PHARMACIESMOREINFO_H
