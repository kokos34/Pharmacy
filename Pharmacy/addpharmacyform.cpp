#include "addpharmacyform.h"
#include "ui_addpharmacyform.h"

AddPharmacyForm::AddPharmacyForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPharmacyForm)
{
    ui->setupUi(this);
}

AddPharmacyForm::~AddPharmacyForm()
{
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

    if(address.isEmpty())
        return false;

    QString regEx = "^[a-zA-Z0-9\s,'-]*$";

    bool correctFormat = address.contains(regEx);

    if(!correctFormat)
        return false;
    else
    {
        listOfElements.append(address);
        return true;
    }

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

    int closingHours = ui->opensAt->text().toInt(&isNumber, 10);

    if(!isNumber)
        return false;

    if(closingHours > 1 && closingHours <= 24)
    {
        if(openingHour == closingHours)
            return false;

        closingHour = closingHours;
        return true;
    }
    else
        return false;
}

bool AddPharmacyForm::isHoursCorrect()
{
    bool isCorrect = isOpeningCorrect() && isClosingCorrect();

    if(isCorrect)
        listOfElements.append(openingHour + "-" + closingHour);

    return isCorrect;
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

    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");

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

bool AddPharmacyForm::getInsertElements()
{
    int indexOfIncorrectStatement = -1;

    for(int i = 0; i < 6; i++)
    {
        switch(i)
        {
        case 0:
            if(!isNameCorrect())
                indexOfIncorrectStatement = 0;
            break;
        case 1:
            if(!isAddressCorrect())
                indexOfIncorrectStatement = 1;
            break;
        case 2:
            if(!isHoursCorrect())
                indexOfIncorrectStatement = 2;
            break;
        case 3:
            if(!isPhoneCorrect())
                indexOfIncorrectStatement = 3;
            break;
        case 4:
            if(!isMailCorrect())
                indexOfIncorrectStatement = 4;
            break;
        case 5:
            fillNote();
            break;
        default:
            break;
        }
    }

    return indexOfIncorrectStatement;
}

void AddPharmacyForm::addPharmacy()
{

}
