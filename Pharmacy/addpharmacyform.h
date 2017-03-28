#ifndef ADDPHARMACYFORM_H
#define ADDPHARMACYFORM_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QSaveFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>

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
    bool addInsertToFile(QString);

    // Testing if elements inserted into line edits are correct
    bool isNameCorrect();
    bool isAddressCorrect();
    bool isHoursCorrect();
    bool isOpeningCorrect();
    bool isClosingCorrect();
    bool isPhoneCorrect();
    bool isMailCorrect();
    void fillNote();

    // Needed to change the file from resource system to local file
    bool setupWritableFile(QSaveFile& dst, QIODevice::OpenMode);
    QString toReadableName(const QString& qrcFileName);
    QString toWritableName(const QString& qrcFileName);
    QStringList readInserts();


    // Needed to concatenate if both end and open hours are correct
    int openingHour;
    int closingHour;

    // File description
    const char* kInsertsFile;

public slots:
    void addPharmacy();
};

#endif // ADDPHARMACYFORM_H
