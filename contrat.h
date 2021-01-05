#ifndef CONTRAT_H
#define CONTRAT_H

#include <QString>
#include <iostream>
#include "gerer.h"
#include "ui_gerer.h"
#include <QtSql/QSqlQueryModel>
class contrat
{  
private:
    int id;
    QString nomp;
    QString duree;
    QString dater;
    int remise;
public:
    contrat();
    contrat(int,QString,QString,QString,int);
    bool ajouter(Ui::Gerer*ui);
    bool modifier(Ui::Gerer*ui);
    bool supprimer (Ui::Gerer*ui);
    void afficher(Ui::Gerer*ui);
    void affichertable(Ui::Gerer*ui);
    void Tri_Prix(Ui::Gerer *ui);
    QSqlQueryModel *triercontrat();
    QSqlQueryModel *triercontrat_desc();
    QSqlQueryModel *recherchercontrat(QString id);
};

#endif // CONTRAT_H
