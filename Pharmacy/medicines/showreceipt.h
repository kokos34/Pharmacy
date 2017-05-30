#ifndef SHOWRECEIPT_H
#define SHOWRECEIPT_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ShowReceipt;
}

class ShowReceipt : public QDialog
{
    Q_OBJECT

public:
    explicit ShowReceipt(QWidget *parent = 0);
    ~ShowReceipt();
    void getMedicineName(QString);
    void showReceiptFile();

private:
    Ui::ShowReceipt *ui;
    QString receiptsText;
    QString medicineName;
};

#endif // SHOWRECEIPT_H
