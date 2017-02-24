#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setAutoFillBackground(true);

    QPixmap bkgnd(":/new/prefix1/bkgrnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);

    QPalette palette;

    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    substituteIconsIntoButtons();

    DatabaseHandler("C:\\Users\\epiokok\\Pharmacy\\my_db.db");
}

MainWindow::~MainWindow()
{
    delete readButton;
    delete infoButton;

    delete readLabel;
    delete infoLabel;

    delete ui;
}

void MainWindow::on_readFromDBButton_clicked()
{
    std::cout << " clicked button " << std::endl;
}

void MainWindow::handleButton()
{
    std::cout << "Button clicked" << std::endl;
}

void MainWindow::substituteIconsIntoButtons()
{
    // Read from db button
    readButton = new QToolButton(this);
    readButton->setGeometry(QRect(QPoint(50, 300), QSize(46, 45)));
    readButton->setIcon(QIcon(":/new/prefix1/read.png"));
    readButton->setIconSize(QSize(46, 45));

    readLabel = new QLabel(this);
    readLabel->setText("Pharmacies info");
    readLabel->setStyleSheet("font-weight: bold; color: blue");
    readLabel->setGeometry(30, 250, 90, 250);

    connect(readButton, SIGNAL (released()), this, SLOT (handleButton()));

    // Display information about medicine
    infoButton = new QToolButton(this);
    infoButton->setGeometry(QRect(QPoint(300, 300), QSize(45, 45)));
    infoButton->setIcon(QIcon(":/new/prefix1/info.png"));
    infoButton->setIconSize(QSize(45, 45));

    infoLabel = new QLabel(this);
    infoLabel->setText("Medicine info");
    infoLabel->setStyleSheet("font-weight: bold; color: blue");
    infoLabel->setGeometry(285, 250, 315, 250);

    connect(infoButton, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}
