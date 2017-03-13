#ifndef MEDICINESHANDLER_H
#define MEDICINESHANDLER_H

#include <QDebug>
#include <QByteArray>

#include "databasehandler.h"

#include <vector>

using namespace ::std;

class MedicinesHandler : public DatabaseHandler
{
public:
    MedicinesHandler();
    MedicinesHandler(const QString& dbPath);
    static vector<vector<QString>> getListOfMedicines();
    static QByteArray* getMedicinePicture(QString name);

private:
    void populateTable();
    bool openInsertFile();
    void loadImages();
    void checkIfThereAreSpecificImages();

    vector<QString> listOfInserts;
    const QString& path = ":/new/prefix1/insertmedicines.txt";
    static QByteArray* picture;
};

#endif // MEDICINESHANDLER_H
