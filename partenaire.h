#ifndef PARTENAIRE_H
#define PARTENAIRE_H
#include <QString>
#include <iostream>
#include "gerer.h"
#include "ui_gerer.h"
#include <QtSql/QSqlQueryModel>

class partenaire
{


private:
    int cin;
    QString nom;
    QString prenom;
    int numtel;
    QString adresse;
    int id;



public:
    partenaire();
    partenaire(int,QString,QString,int,QString,int);
    bool ajouter(Ui::Gerer*ui);
    bool modifier(Ui::Gerer*ui);
    bool supprimer (Ui::Gerer*ui);
    void afficher(Ui::Gerer*ui);
    void affichertable(Ui::Gerer*ui);
    void Tri_partenaire(Ui::Gerer *ui);
    QSqlQueryModel *trierpartenaire();
    QSqlQueryModel *rechercherpartenaire(QString id);
};

#endif // PARTENAIRE_H
