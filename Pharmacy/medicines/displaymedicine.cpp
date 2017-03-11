#include "displaymedicine.h"
#include "ui_displaymedicine.h"

DisplayMedicine::DisplayMedicine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayMedicine)
{
    ui->setupUi(this);
}

DisplayMedicine::~DisplayMedicine()
{
    delete ui;
}

void DisplayMedicine::passPixmapToDisplay(QPixmap map)
{
    ui->label->setPixmap(map);
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}
