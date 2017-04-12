#include "deletepharmacy.h"

DeletePharmacy::DeletePharmacy(QString ph_name)//, QString ph_phone)
{
    name = ph_name;
//    phone = ph_phone;

    insertsFilePath = "C://Users//epiokok//Pharmacy//Pharmacy//pharmacy_inserts.txt";
}

bool DeletePharmacy::updatePharmacyList()
{
    bool readSuccessful = readFromInsertsFile();

    if(readSuccessful)
    {
        updateString(convertToList());

        if(!updatedInserts.isEmpty())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool DeletePharmacy::updateFile()
{
    if(updatePharmacyList())
    {
        QFile insertsFile(insertsFilePath);

        if(insertsFile.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream s(&insertsFile);
            s << updatedInserts;

            insertsFile.close();

            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool DeletePharmacy::readFromInsertsFile()
{
    QFile file(insertsFilePath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        currentInserts = in.readAll();

        return true;
    }
    else
    {
        qDebug() << "Failed to open pharmacy inserts file in read mode";
        return false;
    }
}

QStringList DeletePharmacy::convertToList()
{
    QStringList insertsList;

    insertsList << currentInserts.split("\n");

    QListIterator<QString> i(insertsList);

    while(i.hasNext())
    {
        QString currentElement = i.next();
        //&& currentElement.contains(phone))
        if(currentElement.contains(name))
        {
            insertsList.removeOne(currentElement);
        }
    }
    return insertsList;
}

void DeletePharmacy::updateString(QStringList list)
{
    QListIterator<QString> it(list);

    while(it.hasNext())
    {
        QString current = it.next() + "\n";

        updatedInserts += current;
    }
}
