#ifndef DELETEPHARMACY_H
#define DELETEPHARMACY_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QMutableStringListIterator>
#include <QTextStream>

class DeletePharmacy
{
public:
    DeletePharmacy(QString ph_name);//, QString ph_phone);
    bool updateFile();
private:
    QString name;
//    QString phone;
    QString insertsFilePath;

    QString currentInserts;
    QList<QString> insertsList;
    QString updatedInserts;

    bool readFromInsertsFile();
    QStringList convertToList();
    void updateString(QStringList);
    bool updatePharmacyList();

};

#endif // DELETEPHARMACY_H
