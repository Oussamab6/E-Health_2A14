#include "reservation.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

reservation::reservation()
{

}
reservation::reservation(int id_r,QString nom_pat,QString prenom_pat,QString email_pat,QString date_r,QString sexe_pat)

{
    this->id_r=id_r;
    this->nom_pat=nom_pat;
    this->prenom_pat=prenom_pat;
    this->email_pat=email_pat;
    this->date_r=date_r;
    this->sexe_pat=sexe_pat;



}


int reservation::get_id_r(){return  id_r;}
QString reservation::get_nom_pat(){return nom_pat;}
QString reservation::get_prenom_pat(){return prenom_pat;}
QString reservation::get_email_pat(){return email_pat;}
QString reservation::get_date_r(){return date_r;}
QString reservation::get_sexe_pat(){return sexe_pat;}

bool reservation::ajouter(int id_r,QString nom_pat,QString prenom_pat,QString email_pat,QString date_r,QString sexe_pat)
{
QSqlQuery query;
query.prepare("INSERT INTO menu (ID_R, NOM_PAT, PRENOM_PAT,EMAIL_PAT,DATE_R,SEXE_PAT) "
                    "VALUES (:id_r,:nom_pat,:prenom_pat,:email_pat,:date_r,:sexe_pat)");
query.bindValue(":id_r",id_r);
query.bindValue(":nom_pat",nom_pat);
query.bindValue(":prenom_pat",prenom_pat);
query.bindValue(":email_pat",email_pat);
query.bindValue(":date_r",date_r);
query.bindValue(":sexe_pat",sexe_pat);
return    query.exec();
}

bool reservation::supprimer(int id_r)
{
QSqlQuery query;

query.prepare("Delete from menu where ID_R=:id_r ");
query.bindValue(":id_r",id_r);
return    query.exec();
}

bool reservation::modifier(int id_r,QString nom_pat,QString prenom_pat,QString email_pat,QString date_r,QString sexe_pat)
{QSqlQuery edit;
    edit.prepare("Update menu set nom_pat=:nom_pat, prenom_pat=:prenom_pat, email_pat=:email_pat,date_r=:date_r,sexe_pat=:sexe_pat,where ID_R =:id_r");
    edit.bindValue(":id_r",id_r);
    edit.bindValue(":nom_pat",nom_pat);
    edit.bindValue(":prenom_pat",prenom_pat);
    edit.bindValue(":email_pat",email_pat);
    edit.bindValue(":date_r",date_r);
    edit.bindValue(":sexe_pat",sexe_pat);


    return       edit.exec()  ;
}

QSqlQueryModel * reservation::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * "
                "from reservation");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_r"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_pat"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_pat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("email_pat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_r"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe_pat"));

return model;
}

QSqlQueryModel * reservation::recherche_e(int id_r)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM RESERVATION WHERE id_r LIKE :id_r order by date_r ");
    query.bindValue(":id_r",id_r);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_r"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_pat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_pat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email_pat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_r"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe_pat"));

    return model;
}


QSqlQueryModel * reservation::tri(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
        if(index == 0)
        {
            model->setQuery("select *FROM reservation ORDER BY date ASC");
        }
        else
        {
            model->setQuery("select *FROM  reservation ORDER BY date DESC ");
        }


        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_r"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_pat"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_pat"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("email_pat"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_r"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe_pat"));

        return model;
}









