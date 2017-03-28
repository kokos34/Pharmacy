#include "pharmacieshandler.h"

PharmaciesHandler::PharmaciesHandler()
{

}

PharmaciesHandler::PharmaciesHandler(const QString& path) : DatabaseHandler(path)
{
    // Temporary workaround
    // Since the table doesnt get deleted, every time that the program is ran
    // the table has to be deleted and created from the scratch

    QSqlQuery query;
    bool executed = query.exec("drop table pharmacies");

    if(!executed)
        qDebug() << "not executed";
    else
        qDebug() << "executed";

    createTablePharmacies();

    populateTable();
}

void PharmaciesHandler::populateTable()
{
    if(!openInsertFile(":/new/prefix1/insertstatements.txt"))
    {
        qDebug() << "Failed to populate table";
        return;
    }

    qDebug() << "populate table:";

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
    QFile* insertFile = new QFile(path);

    if (!insertFile->open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed to open insert file";
        return false;
    }

    QTextStream input(insertFile);

    int counter = 0;

    while(!input.atEnd())
    {
        QString currentInsert = input.readLine();
        listOfInserts.push_back(currentInsert);

        counter++;
    }

    insertFile->close();
    delete insertFile;

    return true;
}

vector<vector<QString>> PharmaciesHandler::getListOfPharmacies()
{
    QSqlQuery query;
    bool success = query.exec("select ph_name, ph_address, ph_opening_hours, ph_telephone, ph_email, ph_note from pharmacies");

    if(!success)
        qDebug() << "Failed to select";

    vector<vector<QString>> listOfPharmacies;

    unsigned int rows = sqlSize(query);
    unsigned int rowCounter = 0;

    while(rowCounter < rows)
    {
        query.next();

        vector<QString> currentRow;

        for(int i = 0; i < 6; i++)
        {
            QString currentElement = query.value(i).toString();
            currentRow.push_back(currentElement);
        }
        listOfPharmacies.push_back(currentRow);

        rowCounter++;
    }
    return listOfPharmacies;
}
