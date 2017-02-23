#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("C:\\Users\\epiokok\\Pharmacy\\background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    substituteIconsIntoButtons();
}

MainWindow::~MainWindow()
{
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
    QToolButton* readButton = new QToolButton(this);
    readButton->setGeometry(QRect(QPoint(50, 100), QSize(46, 45)));
    readButton->setIcon(QIcon("C:\\Users\\epiokok\\Pharmacy\\read.png"));
    readButton->setIconSize(QSize(46, 45));

    connect(readButton, SIGNAL (released()), this, SLOT (handleButton()));

    // Display information about medicine
    QToolButton* infoButton = new QToolButton(this);
    infoButton->setGeometry(QRect(QPoint(300, 100), QSize(45, 45)));
    infoButton->setIcon(QIcon("C:\\Users\\epiokok\\Pharmacy\\info.png"));
    infoButton->setIconSize(QSize(45, 45));

    connect(infoButton, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}
