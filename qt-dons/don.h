#ifndef DON_H
#define DON_H

#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>

class don
{
    int id_don;
    int quantite;
    QString emplacement;
    QString date_prelevement;
public:
    don();
    don(int,int,QString,QString);

    int get_id(){return id_don;}
    int get_quantite(){return quantite;}
    QString get_emplacement(){return emplacement;}
    QString get_dateprelev(){return date_prelevement;}


    void set_id(int i){id_don=i;}
    void set_quanite(int q){quantite=q;}
    void set_emplacement(QString e){emplacement=e;}
    void set_dateprelev(QString d){date_prelevement=d;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel *trier(QString,QString);
    QSqlQueryModel *rechercherID(int input);
    QSqlQueryModel *rechercherQuantite(int input);
    QSqlQueryModel *rechercherDate(QString input);


};

#endif // DON_H
