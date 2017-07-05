#ifndef SORTMEDICINES_H
#define SORTMEDICINES_H

#include <QDialog>

namespace Ui {
class SortMedicines;
}

class SortMedicines : public QDialog
{
    Q_OBJECT

public:
    explicit SortMedicines(QWidget *parent = 0);
    ~SortMedicines();
    int getMarkedIndex();

private:
    Ui::SortMedicines *ui;
    int markedIndex;

public slots:
    void sortClicked();
};

#endif // SORTMEDICINES_H
