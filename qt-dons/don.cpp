#include "don.h"

don::don()
{

}
don::don (int i,int q, QString e,QString d):id_don(i),quantite(q),emplacement(e),date_prelevement(d)
{

}
bool don::ajouter()
{
    QSqlQuery query;

    QString res= QString::number(id_don);

    query.prepare("INSERT INTO DON (ID_DON, EMPLACEMENT, QUANTITE, DATE_PRELEV)"
                  "VALUES (:ID_DON, :EMPLACEMENT, :QUANTITE, :DATE_PRELEV)");


    query.bindValue(":ID_DON",res);
    query.bindValue(":EMPLACEMENT",emplacement);
    query.bindValue(":QUANTITE",quantite);
    query.bindValue(":DATE_PRELEV",date_prelevement);

    return query.exec();
}

QSqlQueryModel * don::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from don");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_PRELEV"));

    return model;
}


bool don::supprimer(int ID_DON)
{
    QSqlQuery qry;
    QString id = QString::number(ID_DON);
    qry.prepare("Delete from don where ID_DON = :ID_DON");
    qry.bindValue(":ID_DON",id);
    return qry.exec();
}

QSqlQueryModel *don::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * FROM don order by "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_PRELEV"));

    return model;
}

QSqlQueryModel *don::rechercherID(int input)
{
    QSqlQuery qry;
    qry.prepare("select * from DON where ID_DON =:ID_DON");
    qry.bindValue(":ID_DON",input);
    qry.exec();
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_PRELEV"));


    return model;
}
QSqlQueryModel *don::rechercherQuantite(int input)
{
    QSqlQuery qry;
    qry.prepare("select * from DON where QUANTITE =:QUANTITE");
    qry.bindValue(":QUANTITE",input);
    qry.exec();
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_PRELEV"));


    return model;
}
QSqlQueryModel *don::rechercherDate(QString input)
{
    QSqlQuery qry;
    qry.prepare("select * from DON where lower(date_prelev) like '"+input+"%'");
    qry.exec();
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_PRELEV"));


    return model;
}
