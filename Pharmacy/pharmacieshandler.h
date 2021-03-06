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
    static void refreshPharmacies();
private:
    void populateTable();
    bool openInsertFile(const QString& path);
    static bool populateTableAfterRefresh(const QString& path);

    vector<QString> listOfInserts;
    static vector<QString> listOfNewInserts;
};

#endif // PHARMACIESHANDLER_H
