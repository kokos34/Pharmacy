#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QToolButton>
#include <QPushButton>
#include <QLabel>

#include "pharmacieshandler.h"
#include "pharmaciesform.h"
#include "medicines/medicineshandler.h"
#include "medicines/medicinesform.h"

#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* evt) override;

private slots:
    void pharmaciesButtonClicked();
    void medicinesButtonClicked();

private:
    Ui::MainWindow *ui;
    void substituteIconsIntoButtons();
    QString pathToDB = "/home/kokos/Documents/pharmacy/Pharmacy/my_db.db";
    //"C:\\Users\\epiokok\\Pharmacy\\Pharmacy\\my_db.db";

    bool isDBInitialized = false;

     QLabel* readLabel;
     QLabel* infoLabel;

     QPushButton* readButton;
     QPushButton* infoButton;

     PharmaciesHandler* pharmaciesDB;

     bool isAndroid = true;
};

#endif // MAINWINDOW_H
