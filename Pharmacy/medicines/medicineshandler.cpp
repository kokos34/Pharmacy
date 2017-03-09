#include "medicineshandler.h"

QByteArray* MedicinesHandler::picture = new QByteArray("");

MedicinesHandler::MedicinesHandler()
{

}

MedicinesHandler::MedicinesHandler(const QString& dbPath) : DatabaseHandler(dbPath)
{
    // Temporary workaround
    // Since the table doesnt get deleted, every time that the program is ran
    // the table has to be deleted and created from the scratch

    QSqlQuery query;
    bool executed = query.exec("drop table medicines");

    if(!executed)
        qDebug() << "not executed";
    else
        qDebug() << "executed";

    createTableMedicines();
    populateTable();
    loadImages();
}

void MedicinesHandler::populateTable()
{
    if(!openInsertFile())
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
        qDebug() << "Successfully populated medicines table";
    else
        qDebug() << "Failed to populate medicines table";
}

bool MedicinesHandler::openInsertFile()
{
    QFile* insertFile = new QFile(path);

    if (!insertFile->open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed to open insert file";
        return false;
    }

    qDebug() << "opened file";

    QTextStream input(insertFile);

    int counter = 0;

    while(!input.atEnd())
    {
        QString currentInsert = input.readLine();
        listOfInserts.push_back(currentInsert);

        counter++;
    }

    qDebug() << counter;

    delete insertFile;

    return true;
}

vector<vector<QString>> MedicinesHandler::getListOfMedicines()
{
    QSqlQuery query;

    bool success = query.exec("select med_name, med_quantity_in_bundle, med_for_perscription, med_note from medicines");

    if(!success)
        qDebug() << "Failed to select";

    vector<vector<QString>> listOfMedicines;

    unsigned int rows = DatabaseHandler::sqlSize(query);
    unsigned int rowCounter = 0;

    while(rowCounter < rows)
    {
        query.next();

        vector<QString> currentRow;

        for(int i = 0; i < 4; i++)
        {
            QString currentElement = query.value(i).toString();
            currentRow.push_back(currentElement);
        }
        listOfMedicines.push_back(currentRow);

        rowCounter++;
    }
    return listOfMedicines;
}

void MedicinesHandler::loadImages()
{
    qDebug() << "In insert section";

    QByteArray inByteArray;
    QBuffer inBuffer(&inByteArray);
    QPixmap no_image(":/new/prefix1/no_picture.png");

    inBuffer.open(QIODevice::WriteOnly);
    no_image.save(&inBuffer, "PNG");


    QSqlQuery query;
    query.prepare("UPDATE medicines SET med_picture=:imageData");// WHERE id > 0");
    query.bindValue(":imageData", inByteArray);

    if(!query.exec())
        qDebug() << "Failed to insert images into db";
}

QByteArray* MedicinesHandler::getMedicinePicture(QString medicineName)
{
    QSqlQuery query;

    query.prepare("SELECT med_picture FROM medicines WHERE med_name=:name");
    query.bindValue(":name", medicineName);

    if(!query.exec())
    {
        qDebug() << "Could not display picture";
        return picture;
    }
    else
    {
        query.first();

        qDebug() << "query size = " << sqlSize(query);
        qDebug() << "query.value(0) = " << query.value(1).toString();

        picture = new QByteArray(query.value(0).toByteArray());

        if(picture->isEmpty())
            qDebug() << "byte array is empty";

        return picture;
    }
}
