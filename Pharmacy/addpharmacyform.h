#ifndef ADDPHARMACYFORM_H
#define ADDPHARMACYFORM_H

#include <QDialog>

namespace Ui {
class AddPharmacyForm;
}

class AddPharmacyForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddPharmacyForm(QWidget *parent = 0);
    ~AddPharmacyForm();

private:
    Ui::AddPharmacyForm *ui;
    QString getInsertElements();
    QList<QString> listOfElements;
    QString constructInsert();
    void addInsertToFile(QString);

    // Testing if elements inserted into line edits are correct
    bool isNameCorrect();
    bool isAddressCorrect();
    bool isHoursCorrect();
    bool isOpeningCorrect();
    bool isClosingCorrect();
    bool isPhoneCorrect();
    bool isMailCorrect();
    void fillNote();

    // Needed to concatenate if both end and open hours are correct
    int openingHour;
    int closingHour;

public slots:
    void addPharmacy();
};

#endif // ADDPHARMACYFORM_H
