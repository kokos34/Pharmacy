#ifndef PHARMACIESFORM_H
#define PHARMACIESFORM_H

#include <QDialog>

namespace Ui {
class PharmaciesForm;
}

class PharmaciesForm : public QDialog
{
    Q_OBJECT

public:
    explicit PharmaciesForm(QWidget *parent = 0);
    ~PharmaciesForm();

private:
    Ui::PharmaciesForm *ui;
};

#endif // PHARMACIESFORM_H
