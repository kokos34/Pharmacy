#ifndef MEDICINESHANDLER_H
#define MEDICINESHANDLER_H

#include <QDebug>

#include "databasehandler.h"

#include <vector>

using namespace ::std;

class MedicinesHandler : public DatabaseHandler
{
public:
    MedicinesHandler();
    MedicinesHandler(const QString& dbPath);
    static vector<vector<QString>> getListOfMedicines();

private:
    void populateTable();
    bool openInsertFile();

    vector<QString> listOfInserts;
    const QString& path = ":/new/prefix1/insertmedicines.txt";
};

#endif // MEDICINESHANDLER_H
