#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
private:
    QSqlDatabase test_bd ;

public:
    Connection();
    bool createconnect();
    void fermerconnection() ;
    QSqlDatabase get_db();

};

#endif // CONNECTION_H
