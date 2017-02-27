#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QToolButton>
#include <QPushButton>
#include <QLabel>

#include "pharmacieshandler.h"
#include "pharmaciesform.h"

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
    void on_readFromDBButton_clicked();
    void pharmaciesButtonClicked();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow *ui;
    void substituteIconsIntoButtons();
    QString pathToDB = "C:\\Users\\epiokok\\Pharmacy\\Pharmacy\\my_db.db";
            //"/home/kokos/Documents/pharmacy/Pharmacy/my_db.db";
    bool isDBInitialized = false;

     QLabel* readLabel;
     QLabel* infoLabel;

     QPushButton* readButton;
     QPushButton* infoButton;

     bool isAndroid = true;
};

#endif // MAINWINDOW_H
