#ifndef DISPLAYMEDICINE_H
#define DISPLAYMEDICINE_H

#include <QDialog>

namespace Ui {
class DisplayMedicine;
}

class DisplayMedicine : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayMedicine(QWidget *parent = 0);
    ~DisplayMedicine();

private:
    Ui::DisplayMedicine *ui;
};

#endif // DISPLAYMEDICINE_H
