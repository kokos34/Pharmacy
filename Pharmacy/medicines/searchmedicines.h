#ifndef SEARCHMEDICINES_H
#define SEARCHMEDICINES_H

#include <QDialog>
#include <QMap>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class SearchMedicines;
}

class SearchMedicines : public QDialog
{
    Q_OBJECT

public:
    explicit SearchMedicines(QWidget *parent = 0);
    QMap<QString, int> getResultMap();
    ~SearchMedicines();

public slots:
    void findClicked();

private:
    Ui::SearchMedicines *ui;
    QMap<QString, int> resultMap;
};

#endif // SEARCHMEDICINES_H
