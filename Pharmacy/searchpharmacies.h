#ifndef SEARCHPHARMACIES_H
#define SEARCHPHARMACIES_H

#include <QDialog>

#include <pharmacieshandler.h>

namespace Ui {
class SearchPharmacies;
}

class SearchPharmacies : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPharmacies(QWidget *parent = 0);
    ~SearchPharmacies();

private slots:
    void on_pushButton_clicked();

public slots:
    vector<int> findThePhrase();
    void getListOfPharmacies(vector<vector<QString>>);

private:
    Ui::SearchPharmacies *ui;
    QString searchPhrase;
    vector<int> foundIndexes;

    vector<vector<QString>> listOfPharmacies;
};

#endif // SEARCHPHARMACIES_H
