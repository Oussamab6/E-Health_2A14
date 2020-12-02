#include "form.h"
#include "ui_form.h"
#include "QMessageBox"
#include "medicament.h"
#include <QtDebug>
#include<QThread>

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
     ui->tableView->setModel(m.afficher());
}

Form::~Form()
{
    delete ui;
}


void Form::on_pushButton_ajout_clicked()
{
    QString nom=ui->lineEdit_nom->text();
    int reference=ui->lineEdit_reference->text().toInt();
    int num=ui->lineEdit_nombre->text().toInt();

 medicament e (nom,reference,num);
 bool test=e.ajouter();
 QMessageBox msgBox;

 if(test)
   {       QMessageBox::information(nullptr, QObject::tr("ajout"),
                                    QObject::tr("ajout succes.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tableView->setModel(e.afficher());

                }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("ajout"),
                                    QObject::tr("echec d'ajout.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}


void Form::on_pushButton_mod_clicked()
{
   QString nom= ui->lineEdit_nom_2->text();
    int reference=ui->lineEdit_reference_2->text().toInt();
    int  num= ui->lineEdit_nombre_2->text().toInt() ;

   medicament m (nom,reference,num);
   bool test=m.modifier();
    QMessageBox msgBox;
    if(test)
      {  msgBox.setText("Modifier avec succes.");
        ui->tableView->setModel(m.afficher());
    }
    else
       { msgBox.setText("Echec de modification");
        msgBox.exec();
}
}

void Form::on_pushButton_supp_clicked()
{
    int x =ui->lineEdit_reference_2->text().toInt();
     bool test=m.supprimer(x);
     QMessageBox msgBox;

     if(test)
        {
     msgBox.setText("Suppression avec succes.");
     ui->tableView->setModel(m.afficher());//refreche

     }
     else
         msgBox.setText("Echec de suppression");
         msgBox.exec();
}
void Form::on_tableView_activated(const QModelIndex &index)
{
    medicament m;
       QString val = ui->tableView->model()->data(index).toString();
       QString num_string= QString::number(m.get_num());
       QString reference_string= QString::number(m.get_reference());


       QSqlQuery query;
        query.prepare("select * from MEDICAMENTS where nom=:val or reference=:val or num=:val  ");
        query.bindValue(":val", val);

       if (query.exec())
       {
           while (query.next())
           {
               ui->lineEdit_nom_2->setText(query.value(0).toString());
               ui->lineEdit_reference_2->setText(query.value(1).toString());
               ui->lineEdit_nombre_2->setText(query.value(2).toString());

           }
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("erreur"),
                       QObject::tr("erreur.\n"
                                   "erreur."), QMessageBox::Cancel);       }
}

void Form::on_pushButton_2_clicked()
{
  medicament m;
  ui->tableView->setModel(m.afficher());
}


void Form::on_comboBox_trier_activated(const QString &arg1)
{
    medicament m;
   QSqlQueryModel * modal = new QSqlQueryModel();
   QSqlQuery * qry = new QSqlQuery();
   if (arg1=="Num")
   {
    qry->prepare("Select * from MEDICAMENTS  order by num ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }
  else if (arg1=="Reference")
   {
    qry->prepare("Select * from MEDICAMENTS order by Reference desc");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }

   else if (arg1=="Reference et Nom et Num")
   {
    qry->prepare("Select * from MEDICAMENTS  order by Nom ,num, Reference ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }
}

void Form::on_comboBox_reche_activated(const QString &arg1)
{
        medicament m;
    if(arg1=="Reference")
    {
    m.chercher_reference(ui->lineEdit_reference_2->text().toInt());
    ui->tableView->setModel(m.afficher_reference());
    }
    else if (arg1=="Nom")
    {
        m.chercher_nom(ui->lineEdit_nom_2->text());
        ui->tableView->setModel(m.afficher_nom());

    }
    else if (arg1=="Nom et Num")
    {
        m.chercher_nom_num(ui->lineEdit_nombre_2->text().toInt(),ui->lineEdit_nom_2->text());
        ui->tableView->setModel(m.afficher_nom_num());

    }
}





