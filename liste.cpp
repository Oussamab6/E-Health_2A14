#include "liste.h"
#include "ui_liste.h"
#include "patient.h"
#include <QDebug>
#include <QMessageBox>

liste::liste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::liste)
{
    ui->setupUi(this);
    patient p;
    ui->tab_patient_2->setModel(p.afficher());
}

liste::~liste()
{
    delete ui;
}
/*void liste::on_pushButton_clicked()
{
    int num=ui->Enum->text().toInt();
    QString nom=ui->Enom->text();
    QString prenom=ui->Eprenom->text();
   QString DDN=ui->dateEdit->text();
    int contact=ui->Econtact->text().toInt();
patient p;
    patient p(nom,prenom,DDN,contact,num);

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

}*/
/*}

gestion_des_employe::~gestion_des_employe()
{
    delete ui;
}





void gestion_des_employe::on_ajouter_clicked()
{
    int ref = ui->ref_e->text().toInt();
    QString nom= ui->nom_e->text();
    QString prenom= ui->prenom_e->text();
    QString email=ui->email_e->text();
    QString poste =ui->poste_e->text();
    QString sexe =ui->sex_e->text();
  employee E;
  bool test=false;
  int i;
  for(i=0;i<email.size();i++)
  { if((email[i]=="@")&&((sexe=="homme")||(sexe=="femme")))
          test=true;}
   if(test)E.ajouter(ref,nom,prenom,email,poste,sexe);
  if(test)
{ui->tabemploye_2->setModel(tmpemploye.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un employe"),
                  QObject::tr("employe ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un employé"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
}

}*/
void liste::on_pushButton_clicked()
{
    int num=ui->Enum->text().toInt();
    QString nom=ui->Enom->text();
    QString prenom=ui->Eprenom->text();
   QString DDN=ui->dateEdit->text();
    int contact=ui->Econtact->text().toInt();
patient p(nom,prenom,DDN,contact,num);


bool test=false;

if (num==1 ) {test=true;}
if (test)p.ajouter();
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
void liste::on_pushButton_MODIFIER_clicked()
{
            QString nom= ui->lineEditNom_2->text();
            QString prenom=ui->lineEditPrenom_2->text();
            QString DDN=ui->lineEditDDN_2->text() ;
            int contact=ui->lineEditCONTACT_2->text().toInt();
            int num=ui->lineEditNUM_2->text().toInt();

             patient p(nom,prenom,DDN,contact,num);
           bool test=p.modifier();
            QMessageBox msgBox;
            if(test)
              {  msgBox.setText("Modifier avec succes.");
                ui->tab_patient_2->setModel(p.afficher());
            }
            else
                msgBox.setText("Echec de modification");
                msgBox.exec();
}

void liste::on_pushButton_supp_clicked()
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


void liste::on_tab_patient_2_activated(const QModelIndex &index)
{
    patient P;
    QMessageBox msgBox;

        QString val = ui->tab_patient_2->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("select * from PATIENTEES where NOM =:val or PRENOM =:val or DDN=:val  ");
        query.bindValue(":val", val);

        if (query.exec())
        {
            while (query.next())
            {
                ui->lineEditNom_2->setText(query.value(0).toString());
                ui->lineEditPrenom_2->setText(query.value(1).toString());
                ui->lineEditDDN_2->setDate(query.value(2).toDate());
                ui->lineEditCONTACT_2->setText(query.value(3).toString());
                ui->lineEditNUM_2->setText(query.value(4).toString());
            }
        }
        else
        {
            msgBox.setText("erreur.");
        }
}




void liste::on_comboBox_trier_activated(const QString &arg1)
{
    patient p ;

       QSqlQueryModel * modal = new QSqlQueryModel();
       QSqlQuery * qry = new QSqlQuery();
       if (arg1=="DDN et nom et prenom ")
       {
        qry->prepare("Select * from patientees order by DDN ,NOM,PRENOM");
        qry->exec();
        modal->setQuery(*qry);
        ui->tab_patient_2->setModel(modal);
        ui->tab_patient_2->show();
       }
      else if (arg1=="DDN")
       {
        qry->prepare("Select * from patientees order by DDN");
        qry->exec();
        modal->setQuery(*qry);
        ui->tab_patient_2->setModel(modal);
        ui->tab_patient_2->show();
       }

       else if (arg1=="Num")
       {
        qry->prepare("Select * from patientees order by NUM  ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tab_patient_2->setModel(modal);
        ui->tab_patient_2->show();
       }
}



void liste::on_comboBox_activated(const QString &arg1)
{
    patient p;
        if(arg1=="Num et nom et prenom ")
        {
            p.chercher(ui->lineEditNUM_2->text().toInt(),ui->lineEditNom_2->text(),ui->lineEditPrenom_2->text());
        ui->tab_patient_2->setModel(p.afficher_unepatient());
        }
        else if (arg1=="Num")
        {
           p.chercher_num(ui->lineEditNUM_2->text().toInt());
            ui->tab_patient_2->setModel(p.afficher_unpatient_num());

        }
        else if (arg1=="nom et prenom")
        {
            p.chercher_nom_prenom(ui->lineEditNom_2->text(),ui->lineEditPrenom_2->text());
            ui->tab_patient_2->setModel(p.afficher_unpatient_nom_prenom());

        }
}
int liste::somme()
{
 //radiologue
    int a=0;
bool b=ui->radio->isChecked();
bool b1=ui->radio1->isChecked();
bool b2=ui->radio2->isChecked();
bool b3=ui->radio3->isChecked();
bool b4=ui->radio4->isChecked();
bool b5=ui->radio5->isChecked();

bool tab[7]={b,b1,b2,b3,b4,b5};
  //if (b==true || b1==true ||b2==true ||b3==true ||b4==true ||b6==true ||b5==true ||b7==true ||b8==true)
for (int i(0);i<5 ;i++)
{ if (tab[i]==true)
         a++;
}
//generaliste

bool c=ui->allergo1->isChecked();
bool c1=ui->allergo2->isChecked();
int c2=ui->allergo3->text().toInt();
int c3=ui->allergo4->text().toInt();
  // int som=ui->spinBox_13->text().toInt();*/
bool tab1[2]={c,c1};
for (int i(0);i<2 ;i++)
{ if (tab1[i]==true)
         {a++;}
         a=a+c2+c3;
         return a;
}

   return a;
}
void liste::on_pushButton_7_clicked()
{
int a=somme()*60;

QString a_string=QString::number(a);
//a_string=a"dt";
        //int a=ui->spinBox_13->text().toInt();
QMessageBox msgBox;
//if (a==1)

{ msgBox.setText(a_string);
  msgBox.exec();
}
/*else if (a==0)
{msgBox.setText("free");
    msgBox.exec();}*/


}
