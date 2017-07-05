#include "addmedicine.h"
#include "ui_addmedicine.h"

AddMedicine::AddMedicine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMedicine)
{
    ui->setupUi(this);

    connect(ui->addMedicine, SIGNAL(clicked()), this, SLOT(addNewMedicine()));
    connect(ui->addMedicine, SIGNAL(clicked()), this, SLOT(accept()));
}

AddMedicine::~AddMedicine()
{
    delete ui;
}

bool AddMedicine::openInsertFile()
{
    QFile insertsFile("C:\\Users\\epiokok\\Pharmacy\\Pharmacy\\insertmedicines.txt");
    insertsFile.open(QIODevice::ReadWrite);

    if(!insertsFile.isOpen())
        return false;

    QTextStream s(&insertsFile);
    insertsList = s.readAll();

    insertsFile.close();

    if(!insertsList.isEmpty())
        return true;
    else
        return false;
}

void AddMedicine::addNewMedicine()
{
    if(!openInsertFile())
    {
        QMessageBox::information(this, "Error!", "Problem while reading current medicines");
        return;
    }

    const int nameIncorrect = 0;
    const int quantityIncorrect = 1;
    const int allCorrect = 2;

    int checkDataResult = checkGivenData();

    switch(checkDataResult)
    {
    case nameIncorrect:
        QMessageBox::information(this, "Error!", "Medicine name is empty");
        break;
    case quantityIncorrect:
        QMessageBox::information(this, "Error!", "Medicine name is empty");
        break;
    case allCorrect:
        QString newInsert = constructNewInsert();
        bool success = addInsertToFile(newInsert);
        if(!success)
            QMessageBox::information(this, "Error", "Failed to add new medicine");
        else
            QMessageBox::information(this, "Note", "Successfully added new medicine");
    }
}

int AddMedicine::checkGivenData()
{
    // Medicine name
    if(ui->medName->text().isEmpty())
        return 0;
    // Quantity in bundle
    QString quant = ui->quant->text();
    bool conversion;

    quant.toDouble(&conversion);

    if(!conversion)
        return 1;

    return 2;
}

QString AddMedicine::constructNewInsert()
{
    QString isForPerscription;

    if(ui->perscription->isChecked())
        isForPerscription = "yes";
    else
        isForPerscription = "no";

    return "insert into medicines('med_name', 'med_quantity_in_bundle', 'med_for_perscription', 'med_note') values('" +
            ui->medName->text() + "', '" + ui->quant->text() + "', '" + isForPerscription + "','" + ui->note->text() + "');";
}

bool AddMedicine::addInsertToFile(QString insert)
{
    insertsList = insertsList + "\n" + insert;

    QFile insertsFile("C:\\Users\\epiokok\\Pharmacy\\Pharmacy\\insertmedicines.txt");
    insertsFile.open(QIODevice::ReadWrite);

    if(!insertsFile.isOpen())
        return false;

    QTextStream s(&insertsFile);
    s << insertsList;

    insertsFile.close();

    return true;
}
