#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <iostream>

#include <QtSql>

class DatabaseHandler
{
public:
    // If database was not created earlier
    DatabaseHandler(const QString& path);
    // If database exists
    DatabaseHandler();

    void createTablePharmacies();
    void createTableMedicines();

    static int sqlSize(QSqlQuery);
protected:
    QSqlDatabase pharmacies_db;
};

#endif // DATABASEHANDLER_H
