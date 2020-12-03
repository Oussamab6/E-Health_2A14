#include "connecion.h"
#include <QSqlError>
connecion::connecion(){}
bool connecion::ouvrirconnexion(){
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("souheil");
    db.setPassword("souheil");
    if(db.open())
    test=true;
    else throw QString ("Erreur Paramétres"+db.lastError().text());
    return test;}

void connecion::fermerconnexion(){
    db.close();
}
