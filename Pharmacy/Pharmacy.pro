#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T20:30:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pharmacy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    databasehandler.cpp \
    pharmacieshandler.cpp \
    pharmaciesform.cpp \
    pharmaciesmoreinfo.cpp \
    searchpharmacies.cpp \
    medicines/medicinesform.cpp \
    sortpharmacies.cpp \
    medicines/medicineshandler.cpp \
    medicines/searchmedicines.cpp \
    medicines/displaymedicine.cpp

HEADERS  += mainwindow.h \
    databasehandler.h \
    pharmacieshandler.h \
    pharmaciesform.h \
    pharmaciesmoreinfo.h \
    searchpharmacies.h \
    medicines/medicinesform.h \
    sortpharmacies.h \
    medicines/medicineshandler.h \
    medicines/searchmedicines.h \
    medicines/displaymedicine.h

FORMS    += \
    mainwindow.ui \
    pharmaciesform.ui \
    pharmaciesmoreinfo.ui \
    searchpharmacies.ui \
    medicines/medicinesform.ui \
    sortpharmacies.ui \
    medicines/searchmedicines.ui \
    medicines/displaymedicine.ui

CONFIG += mobility
MOBILITY = 

DISTFILES +=

RESOURCES += \
    icons.qrc

