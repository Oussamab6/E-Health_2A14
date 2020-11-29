#include "salledattente.h"
#include "ui_salledattente.h"

salledattente::salledattente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salledattente)
{
    ui->setupUi(this);
}

salledattente::~salledattente()
{
    delete ui;
}
