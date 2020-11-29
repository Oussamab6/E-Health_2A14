#include "patient.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>



patient::patient (QString nom,QString prenom,int j,int m,int a ,int contact,int num)
{
this->nom=nom;
    this->prenom=prenom;
    this->j=j;
    this->m=m;
    this->a=a;
    this->contact=contact;
     this->num=num;
}

bool patient::ajouter()
{
QSqlQuery query;
QString num_string=QString::number(num);
QString j_string=QString::number(j);
QString m_string=QString::number(m);
QString a_string=QString::number(a);
QString contact_string=QString::number(contact);
query.prepare("INSERT INTO patients (NOM,PRENOM,J,M,A,CONTACT,NUM) "
              "VALUES (:nom, :prenom, :j,:m,:a,:contact,:num)");

query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":j",j_string);
query.bindValue(":m",m_string);
query.bindValue(":a",a_string);
query.bindValue(":contact",contact_string);
query.bindValue(":num",num_string);
return query.exec();
}

QSqlQueryModel* patient::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM patients");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("j"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("m"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("a"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("contact"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("num"));

  return  model;
}

bool patient::supprimer(int num)
{
    QSqlQuery query;
         query.prepare(" Delete from patients where num=:num");
         query.bindValue(":num", num);

        return query.exec();


}
