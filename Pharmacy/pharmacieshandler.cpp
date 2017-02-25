#include "pharmacieshandler.h"

PharmaciesHandler::PharmaciesHandler()
{

}

PharmaciesHandler::PharmaciesHandler(const QString& path) : DatabaseHandler(path)
{
    createTablePharmacies();
}
