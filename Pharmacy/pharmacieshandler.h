#ifndef PHARMACIESHANDLER_H
#define PHARMACIESHANDLER_H

#include "databasehandler.h"
#include <vector>

class PharmaciesHandler : public DatabaseHandler
{
public:
    PharmaciesHandler();
    PharmaciesHandler(const QString& path);
private:
    void populateTable();
    bool openInsertFile(const QString& path);
    std::vector<QString> listOfInserts;
};

#endif // PHARMACIESHANDLER_H
