#include "databasehandler.h"

DatabaseHandler::DatabaseHandler(const QString& path)
{
    pharmacies_db = QSqlDatabase::addDatabase("QSQLITE");
    pharmacies_db.setDatabaseName(path);

    if(!pharmacies_db.open())
        qDebug() << "Error connection to DB failed";
    else
        qDebug() << "Successfully connected to database";

    createTablePharmacies();
    createTableMedicines();
}

void DatabaseHandler::createTablePharmacies()
{
    QSqlQuery query;
    bool success = query.exec("create table if not exists pharmacies "
              "(id integer primary key, "
              "ph_name varchar(30), "
              "ph_address varchar(30), "
              "ph_opening_hours varchar(5))");

    if(success)
        qDebug() << "Successfully created pharmacies table";
    else
        qDebug() << "Failed to create pharmacies table or table exists";
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
        qDebug() << "Failed to create medicines table or table exists";
}
