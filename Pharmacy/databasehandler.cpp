#include "databasehandler.h"

DatabaseHandler::DatabaseHandler(const QString& path)
{
    pharmacies_db = QSqlDatabase::addDatabase("QSQLITE");
    pharmacies_db.setDatabaseName(path);

    if(!pharmacies_db.open())
        qDebug() << "Error: connection to DB failed";
    else
        qDebug() << "Successfully connected to database";
}

DatabaseHandler::DatabaseHandler()
{
    qDebug() << "Database already exists, proceeding...";
}

void DatabaseHandler::createTablePharmacies()
{
    QSqlQuery query;
    bool success = query.exec("create table if not exists pharmacies "
              "(id integer primary key autoincrement, "
              "ph_name varchar(30), "
              "ph_address varchar(30), "
              "ph_opening_hours varchar(5), "
              "ph_telephone varchar(9), "
              "ph_email varchar(25), "
              "ph_note varchar(50))");

    if(success)
        qDebug() << "Successfully created pharmacies table";
    else
        qDebug() << "Failed to create pharmacies table";
}

void DatabaseHandler::createTableMedicines()
{
    QSqlQuery query;
    bool success = query.exec("create table if not exists medicines "
              "(id integer primary key, "
              "med_name varchar(30) not null, "
              "med_quantity_in_bundle integer not null, "
              "med_for_perscription integer not null, "
              "med_note varchar(50))");

    if(success)
        qDebug() << "Successfully created medicines table";
    else
        qDebug() << "Failed to create medicines table";
}

int DatabaseHandler::sqlSize(QSqlQuery query)
{
    int initialPos = query.at();
    // Very strange but for no records .at() returns -2
    int pos = 0;
    if (query.last())
        pos = query.at() + 1;
    else
        pos = 0;
    // Important to restore initial pos
    query.seek(initialPos);
    return pos;
}
