#include "gestion_de_pation.h"
#include "ui_gestion_de_pation.h"
#include "patient.h"
#include "liste.h"
#include <QDebug>
#include <QMessageBox>

Gestion_de_pation::Gestion_de_pation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_de_pation)
{
    ui->setupUi(this);
    patient p;
    ui->tab_patient_2->setModel(p.afficher());

}

Gestion_de_pation::~Gestion_de_pation()
{
    delete ui;
}
void Gestion_de_pation:: on_pushButton_5_clicked()
{liste l;
l.exec();
}


void Gestion_de_pation::on_pushButton_clicked()
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
             ui->tab_patient_2->setModel(p.afficher());
}
        else
           msgBox.setText("echec");
         msgBox.exec();

}
void Gestion_de_pation::on_supprimer_clicked()
{
    patient p1;
    int x=ui->lineEdit->text().toInt();
    bool test=p1.supprimer(x);
    QMessageBox msgBox;

    if(test)
       {
       msgBox.setText("Suppression avec succes.");
       ui->tab_patient_2->setModel(p1.afficher());
}

    else
       { msgBox.setText("Echec de suppression");
        msgBox.exec();}
}
