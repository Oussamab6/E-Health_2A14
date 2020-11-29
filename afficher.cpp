#include "afficher.h"
#include "ui_afficher.h"

afficher::afficher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afficher)
{
    ui->setupUi(this);
}

afficher::~afficher()
{
    delete ui;
}
