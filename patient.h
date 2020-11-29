#ifndef PATIENT_H
#define PATIENT_H
#include <string.h>
#include<QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


class patient
{
    QString nom,prenom;
    int  j,m,a,contact,num;
public:
    patient(){}
    patient(QString,QString,int,int,int,int,int);
    //getters
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getj(){return j;}
    int getm(){return m;}
    int geta() {return a;}
    int getcontact() {return contact;}
      int getnum() {return num;}
    //setters
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setj(int j){this->j=j;}
    void setm(int m){this->m=m;}
    void seta(int a){this->a=a;}
    void setcontact(int contact){this->contact=contact;}
    void setnum(int num){this->num=num;}
    //fonction
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
};
#endif // PATIENT_H*/
