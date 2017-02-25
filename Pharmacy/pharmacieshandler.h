#ifndef PHARMACIESHANDLER_H
#define PHARMACIESHANDLER_H

#include "databasehandler.h"

class PharmaciesHandler : public DatabaseHandler
{
public:
    PharmaciesHandler();
    PharmaciesHandler(const QString& path);
private:
    void populateTable();
};

#endif // PHARMACIESHANDLER_H
