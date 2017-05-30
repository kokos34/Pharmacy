#include "sortmedicines.h"
#include "ui_sortmedicines.h"

SortMedicines::SortMedicines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortMedicines)
{
    ui->setupUi(this);

    connect(ui->sortMedicines, SIGNAL(clicked()), this, SLOT(sortClicked()));
    connect(ui->sortMedicines, SIGNAL(clicked()), this, SLOT(accept()));
}

SortMedicines::~SortMedicines()
{
    delete ui;
}

void SortMedicines::sortClicked()
{
    markedIndex = ui->comboBox->currentIndex();
}

int SortMedicines::getMarkedIndex()
{
    return markedIndex;
}
