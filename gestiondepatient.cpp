#include "gestiondepatient.h"
#include "ui_gestiondepatient.h"
#include "patient.h"
#include "liste.h"
#include <QDebug>
#include <QMessageBox>

gestiondepatient::gestiondepatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestiondepatient)
{
    ui->setupUi(this);
ui->Enum->setValidator(new QIntValidator(100, 999, this));

}

gestiondepatient::~gestiondepatient()
{
    delete ui;
}

void gestiondepatient:: on_pushButton_5_clicked()
{liste l;
l.exec();
}


void gestiondepatient::on_pushButton_clicked()
{
    int num=ui->Enum->text().toInt();
    QString nom=ui->Enom->text();
    QString prenom=ui->Eprenom->text();
     int j=ui->Ej->text().toInt();
     int m=ui->Em->text().toInt();
     int a=ui->Ea->text().toInt();
     int contact=ui->Econtact->text().toInt();
   patient p(nom,prenom,j,m,a,contact,num);

bool test=p.ajouter();
QMessageBox msgBox;

        if (test)
     {
             msgBox.setText("ajout avec succés");
             ui->tab_patient->setModel(p.afficher());
}
        else
           msgBox.setText("echec");
         msgBox.exec();

}
void gestiondepatient::on_supprimer_clicked()
{
    patient p1;
    p1.setnum(ui->lineEdit->text().toInt());
    bool test=p1.supprimer(p1.getnum());

    QMessageBox msgBox;

    if(test)
       {msgBox.setText("Suppression avec succes.");
       ui->tab_patient->setModel(p1.afficher());
}

    else
       { msgBox.setText("Echec de suppression");
        msgBox.exec();}
}








