#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setAutoFillBackground(true);

//    if(isAndroid)
//        this->setWindowState(Qt::WindowFullScreen);

    QPixmap bkgnd(":/new/prefix1/bkgrnd.png");
    bkgnd = bkgnd.scaled(this->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    substituteIconsIntoButtons();
}

MainWindow::~MainWindow()
{
    delete readButton;
    delete infoButton;

    delete readLabel;
    delete infoLabel;

    delete ui;
}

void MainWindow::substituteIconsIntoButtons()
{
    // Read from db button
    readButton = new QPushButton(this);
    readButton->setGeometry(QRect(QPoint(50, 300), QSize(46, 45)));
    readButton->setIcon(QIcon(":/new/prefix1/read.png"));
    readButton->setIconSize(QSize(46, 45));

    readLabel = new QLabel(this);
    readLabel->setText("Pharmacies");
    readLabel->setStyleSheet("font-weight: bold; color: blue");
    readLabel->setGeometry(30, 150, 90, 150);

    connect(readButton, SIGNAL (released()), this, SLOT (pharmaciesButtonClicked()));

    // Display information about medicine
    infoButton = new QPushButton(this);
    infoButton->setGeometry(QRect(QPoint(300, 300), QSize(45, 45)));
    infoButton->setIcon(QIcon(":/new/prefix1/info.png"));
    infoButton->setIconSize(QSize(45, 45));

    infoLabel = new QLabel(this);
    infoLabel->setText("Medicines");
    infoLabel->setStyleSheet("font-weight: bold; color: blue");
    infoLabel->setGeometry(285, 150, 315, 150);

    //connect(infoButton, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::pharmaciesButtonClicked()
{
    PharmaciesHandler* pharmaciesDB;

    if(!isDBInitialized)
    {
        pharmaciesDB = new PharmaciesHandler(pathToDB);
        isDBInitialized = true;
    }
    else
    {
        pharmaciesDB = new PharmaciesHandler();
    }

    PharmaciesForm phDialog;
    phDialog.setModal(true);
    phDialog.exec();
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/new/prefix1/bkgrnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(evt); // call inherited implementation
}
