#include "searchpharmacies.h"
#include "ui_searchpharmacies.h"

SearchPharmacies::SearchPharmacies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPharmacies)
{
    ui->setupUi(this);

    ui->label->setStyleSheet("font-weight: bold; color: green");
    ui->label_2->setStyleSheet("font-weight: bold; color: green");

    ui->comboBox_2->setVisible(false);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(findThePhrase()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));

    //176x162
}

SearchPharmacies::~SearchPharmacies()
{
    delete ui;
}

vector<int> SearchPharmacies::findThePhrase()
{
    return foundIndexes;
}

void SearchPharmacies::on_pushButton_clicked()
{
    int columnIndex = ui->comboBox->currentIndex();
    searchPhrase = ui->textEdit->toPlainText();

    vector<vector<QString>> dbRecords = PharmaciesHandler::getListOfPharmacies();

    for(unsigned int i = 0; i < dbRecords.size(); i++)
    {
        if(columnIndex!=0)
        {
            int result = 1;

            if((result = QString::compare(dbRecords[i][columnIndex-1], searchPhrase, Qt::CaseInsensitive)) == 0)
                foundIndexes.push_back(i);
        }
        else
        {
            for(int column = 0; column < dbRecords[0].size(); column++)
            {
                int result = 1;

                if((result = QString::compare(dbRecords[i][column], searchPhrase, Qt::CaseInsensitive)) == 0)
                    foundIndexes.push_back(i);
            }
        }
    }
}

void SearchPharmacies::on_comboBox_2_currentIndexChanged(int index)
{
    //emit this->on_pushButton_clicked();
}
