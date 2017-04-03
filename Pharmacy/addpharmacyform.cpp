#include "addpharmacyform.h"
#include "ui_addpharmacyform.h"

AddPharmacyForm::AddPharmacyForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPharmacyForm)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addPharmacy()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));
}

AddPharmacyForm::~AddPharmacyForm()
{
    listOfElements.clear();
    delete ui;
}

bool AddPharmacyForm::isNameCorrect()
{
    QString name = ui->name->text();

    if(name.isEmpty())
        return false;
    else
    {
        listOfElements.append(name);
        return true;
    }
}

bool AddPharmacyForm::isAddressCorrect()
{
    QString address = ui->address->text();
    bool isNumber;
    int streetNumber = ui->stNumber->text().toInt(&isNumber, 10);

    if(!isNumber)
        return false;

    if(address.isEmpty())
        return false;

    if(!address.contains(QRegExp("[A-Z]+")))
        return false;

    listOfElements.append(address + " " + QString::number(streetNumber));

    return true;

}

bool AddPharmacyForm::isOpeningCorrect()
{
    bool isNumber;

    int openingHours = ui->opensAt->text().toInt(&isNumber, 10);

    if(!isNumber)
        return false;

    if(openingHours > 1 && openingHours <= 24)
    {
        openingHour = openingHours;
        return true;
    }
    else
        return false;
}

bool AddPharmacyForm::isClosingCorrect()
{
    bool isNumber;

    int closingHours = ui->closesAt->text().toInt(&isNumber, 10);

    if(!isNumber)
    {
        qDebug() << "invalid conversion";
        return false;
    }

    if(closingHours > 1 && closingHours <= 24)
    {
        if(openingHour == closingHours)
        {
            qDebug() << "same opening and closing";

            return false;
        }

        closingHour = closingHours;
        return true;
    }
    else
    {
        qDebug() << "too big or too small number";
        return false;
    }
}

bool AddPharmacyForm::isHoursCorrect()
{
    bool isCorrect = isOpeningCorrect() && isClosingCorrect();

    if(isCorrect)
    {
        qDebug() << "opening= " << openingHour << " closing= " << closingHour;

        listOfElements.append(QString::number(openingHour) + "-" + QString::number(closingHour));
        return true;
    }
    else
    {
        qDebug() << "opening = " << isOpeningCorrect() << " closing = " << isClosingCorrect();
        return false;
    }
}

bool AddPharmacyForm::isPhoneCorrect()
{
    QString phone = ui->phone->text();
    bool isNumber;

    phone.toInt(&isNumber, 10);

    if(!isNumber)
        return false;

    if(phone.length() == 9 || phone.length() == 10)
    {
        listOfElements.append(phone);
        return true;
    }
    else
        return false;
}

bool AddPharmacyForm::isMailCorrect()
{
    QString mail = ui->mail->text();

    QRegExp mailREX("[A-Za-z0-9.-]+@{1}[\\w]{2,}\\.[\\w]{2,4}");

    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);

    bool isCorrect = mail.contains(mailREX);

    if(!isCorrect)
        return false;
    else
    {
        listOfElements.append(mail);
        return true;
    }
}

void AddPharmacyForm::fillNote()
{
    QString note = ui->note->text();

    listOfElements.append(note);
}

QString AddPharmacyForm::getInsertElements()
{
    QString statement = "";

    for(int i = 0; i < 6; i++)
    {
        switch(i)
        {
        case 0:
            if(!isNameCorrect())
                statement = "Name is incorrect!";
            break;
        case 1:
            if(!isAddressCorrect())
                statement = "Address is incorrect!";
            break;
        case 2:
            if(!isHoursCorrect())
                statement = "Hours are incorrect!";
            break;
        case 3:
            if(!isPhoneCorrect())
                statement = "Phone is incorrect!";
            break;
        case 4:
            if(!isMailCorrect())
                statement = "Mail is incorrect!";
            break;
        case 5:
            fillNote();
            break;
        default:
            break;
        }
    }

    return statement;
}

QString AddPharmacyForm::constructInsert()
{
    QString insert = "";

    insert += "insert into pharmacies('ph_name', 'ph_address', 'ph_opening_hours',"
              " 'ph_telephone', 'ph_email', 'ph_note') values('" +
              listOfElements[0] + "', '" + listOfElements[1] + "', '" +
              listOfElements[2] + "', '" + listOfElements[3] + "', '" +
              listOfElements[4] + "', '" + listOfElements[5] + "');";

    return insert;
}

bool AddPharmacyForm::addInsertToFile(QString insert)
{
    makeALocalCopyOfFile();

    insertsFile = new QFile();
    insertsFile->setFileName("C://Users//epiokok//Pharmacy//Pharmacy//" + kInsertsFile);

    if(!insertsFile->exists())
        qDebug() << "File does not exist! " << insertsFile->fileName();

    if(insertsFile->isOpen())
       qDebug() << "File is open";

    if(!insertsFile->isWritable())
        qDebug() << "File is not writeable";

    if(insertsFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream s(insertsFile);
        QString newInserts = currentInserts + "\n" + insert;
        s << newInserts;

        insertsFile->close();
        delete insertsFile;

        return true;
    }
    else
        return false;
}
void AddPharmacyForm::makeALocalCopyOfFile()
{
    insertsFile = new QFile();
    insertsFile->setFileName("C://Users//epiokok//Pharmacy//Pharmacy//" + kInsertsFile);

    if(insertsFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "opened file in readmode";
        QTextStream in(insertsFile);
        currentInserts = in.readAll();
    }
    else
        qDebug() << "failed to open file in read mode";

    insertsFile->close();
    delete insertsFile;
}

void AddPharmacyForm::addPharmacy()
{
    QString errorStatement = getInsertElements();
    QString insert;

    if(errorStatement.isEmpty())
    {
        insert = constructInsert();
        auto status = addInsertToFile(insert);

        if(!status)
            QMessageBox::information(this, tr("Fail"), tr("Failed to add new pharmacy"));
        else
            QMessageBox::information(this, tr("Success"), tr("Successfully added new pharmacy"));
    }
    else
        QMessageBox::information(this, tr("Error"), tr(errorStatement.toLatin1().data()));
}
