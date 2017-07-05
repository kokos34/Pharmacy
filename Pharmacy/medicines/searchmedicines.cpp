#include "searchmedicines.h"
#include "ui_searchmedicines.h"

SearchMedicines::SearchMedicines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchMedicines)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));
}

SearchMedicines::~SearchMedicines()
{
    delete ui;
}

QMap<QString, int> SearchMedicines::getResultMap()
{
    return resultMap;
}

void SearchMedicines::findClicked()
{
    QString findPhrase = ui->textEdit->toPlainText();

    if(findPhrase.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Search phrase is empty") );
        return;
    }

    int index = ui->comboBox->currentIndex();

    if(index == -1)
    {
        QMessageBox::information(this, tr("Error"), tr("Please select by which column we should search") );
        return;
    }

    resultMap.insert(findPhrase, index);
    qDebug() << "findPhrase = " << findPhrase << " index = " << QString::number(index);
}
