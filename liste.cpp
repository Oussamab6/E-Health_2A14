#include "liste.h"
#include "ui_liste.h"
#include "gestion_de_pation.h"
#include "facturation.h"
#include "gesiondedm.h"

liste::liste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::liste)
{
    ui->setupUi(this);
}

liste::~liste()
{
    delete ui;
}
void liste :: on_pushButton_5_clicked()
{
    facturation f;
    f.exec();
}

void liste :: on_pushButton_2_clicked()
{
    Gestion_de_pation g;
    g.exec();
}

void liste :: on_pushButton_3_clicked()
{
    gesiondedm dm;
    dm.exec();
}
