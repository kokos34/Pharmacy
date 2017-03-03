#ifndef PHARMACIESHANDLER_H
#define PHARMACIESHANDLER_H

#include "databasehandler.h"
#include <vector>

using namespace::std;

class PharmaciesHandler : public DatabaseHandler
{
public:
    PharmaciesHandler();
    PharmaciesHandler(const QString& path);
    static vector<vector<QString>> getListOfPharmacies();
private:
    void populateTable();
    bool openInsertFile(const QString& path);
    vector<QString> listOfInserts;
};

#endif // PHARMACIESHANDLER_H
