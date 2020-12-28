#include "connection.h"
//test git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase test_bd = QSqlDatabase::addDatabase("QODBC");
test_bd.setDatabaseName("test-bd");//inserer le nom de la source de données ODBC
test_bd.setUserName("hadriche");//inserer nom de l'utilisateur
test_bd.setPassword("hadriche");//inserer mot de passe de cet utilisateur


if (test_bd.open())
test=true;





    return  test;
}
    void Connection::fermerconnection()
    {

        test_bd.close();
    }

