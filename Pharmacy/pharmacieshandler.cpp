#include "pharmacieshandler.h"

PharmaciesHandler::PharmaciesHandler()
{

}

PharmaciesHandler::PharmaciesHandler(const QString& path) : DatabaseHandler(path)
{
    createTablePharmacies();
    populateTable();
}

void PharmaciesHandler::populateTable()
{
    if(!openInsertFile("/home/kokos/Documents/pharmacy/Pharmacy/Pharmacy/insertstatements.txt"))
        return;

    bool allInsertsSucceeded = true;

    for(unsigned short i = 0; i < listOfInserts.size(); i++)
    {
        QSqlQuery query;
        bool success = query.exec(listOfInserts[i]);

        if(!success)
            allInsertsSucceeded = false;
    }

    if(allInsertsSucceeded)
        qDebug() << "Successfully populated pharmacies table";
    else
        qDebug() << "Failed to populate pharmacies table";
}

bool PharmaciesHandler::openInsertFile(const QString& path)
{
    QFile insertFile(path);

    if (!insertFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed to open insert file";
        return false;
    }

    QTextStream input(&insertFile);

    while(!input.atEnd())
    {
        QString currentInsert = input.readLine();
        listOfInserts.push_back(currentInsert);
    }

    return true;
}
