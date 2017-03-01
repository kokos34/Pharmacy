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
    QString myVal() const {  }

private slots:
    void on_comboBox_2_currentIndexChanged(int index);
    void on_pushButton_clicked();

public slots:
    vector<int> findThePhrase();

private:
    Ui::SearchPharmacies *ui;
    QString searchPhrase;
    vector<int> foundIndexes;
};

#endif // SEARCHPHARMACIES_H
