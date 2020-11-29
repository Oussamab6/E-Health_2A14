#include "gesiondedm.h"
#include "ui_gesiondedm.h"
#include"liste.h"

gesiondedm::gesiondedm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gesiondedm)
{
    ui->setupUi(this);
}

gesiondedm::~gesiondedm()
{
    delete ui;
}
void gesiondedm:: on_pushButton_clicked()
{
    liste l;
    l.exec();
}
