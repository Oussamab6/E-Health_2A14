#ifndef CONNECION_H
#define CONNECION_H
#include <QSqlDatabase>
#include <QSqlError>

class connecion
{
private:
    QSqlDatabase db;
public:
    connecion();
    bool ouvrirconnexion();
    void fermerconnexion();
};

#endif // CONNECION_H
