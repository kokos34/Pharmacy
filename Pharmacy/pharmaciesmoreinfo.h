#ifndef PHARMACIESMOREINFO_H
#define PHARMACIESMOREINFO_H

#include <QDialog>

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

private:
    Ui::PharmaciesMoreInfo *ui;
    int rowIndexFromParent;
};

#endif // PHARMACIESMOREINFO_H
