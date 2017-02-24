#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <iostream>

#include <QtSql>

class DatabaseHandler
{
public:
    DatabaseHandler(const QString& path);
    //void executeQuery(const QString& queryText);
private:
    QSqlDatabase pharmacies_db;
    void createTablePharmacies();
    void createTableMedicines();
};

#endif // DATABASEHANDLER_H
