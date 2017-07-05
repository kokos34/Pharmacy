#include "sortpharmacies.h"
#include "ui_sortpharmacies.h"

SortPharmacies::SortPharmacies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortPharmacies)
{
    ui->setupUi(this);

    connect(ui->sortButton, SIGNAL(clicked()), this, SLOT(sortClicked()));
    connect(ui->sortButton, SIGNAL(clicked()), this, SLOT(accept()));
}

SortPharmacies::~SortPharmacies()
{
    delete ui;
}

void SortPharmacies::sortClicked()
{
    markedIndex = ui->comboBox->currentIndex();
}

int SortPharmacies::getMarkedIndex()
{
    return markedIndex;
}
