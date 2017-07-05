#include "showreceipt.h"
#include "ui_showreceipt.h"

ShowReceipt::ShowReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowReceipt)
{
    ui->setupUi(this);
}

ShowReceipt::~ShowReceipt()
{
    delete ui;
}

void ShowReceipt::showReceiptFile()
{
    QFile receiptFile("C:\\Users\\epiokok\\Pharmacy\\Pharmacy\\" + medicineName + ".txt");
    receiptFile.open(QIODevice::ReadOnly);

    if(receiptFile.isOpen())
    {
        QTextStream in(&receiptFile);
        receiptsText = in.readAll();
    }
    else
        receiptsText = "No perscription found for this medicine";

    ui->textBrowser->setText(receiptsText);
    ui->textBrowser->setReadOnly(true);
}

void ShowReceipt::getMedicineName(QString name)
{
    medicineName = name;
}
