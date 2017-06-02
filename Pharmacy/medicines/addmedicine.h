#ifndef ADDMEDICINE_H
#define ADDMEDICINE_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class AddMedicine;
}

class AddMedicine : public QDialog
{
    Q_OBJECT

public:
    explicit AddMedicine(QWidget *parent = 0);
    ~AddMedicine();

public slots:
    void addNewMedicine();

private:
    Ui::AddMedicine *ui;
    bool openInsertFile();
    int checkGivenData();
    QString constructNewInsert();
    bool addInsertToFile(QString);

    QString insertsList;
};

#endif // ADDMEDICINE_H
