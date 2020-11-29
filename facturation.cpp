#include "facturation.h"
#include "ui_facturation.h"

facturation::facturation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facturation)
{
    ui->setupUi(this);
}

facturation::~facturation()
{
    delete ui;
}
