#ifndef SORTPHARMACIES_H
#define SORTPHARMACIES_H

#include <QDialog>

namespace Ui {
class SortPharmacies;
}

class SortPharmacies : public QDialog
{
    Q_OBJECT

public:
    explicit SortPharmacies(QWidget *parent = 0);
    ~SortPharmacies();
    int getMarkedIndex();

private:
    Ui::SortPharmacies *ui;
    int markedIndex;

public slots:
    void sortClicked();
};

#endif // SORTPHARMACIES_H
