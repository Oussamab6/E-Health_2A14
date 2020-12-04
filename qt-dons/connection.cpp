#include "connection.h"
#include "QSqlDatabase"
connection::connection()
{

}

bool connection::createConnection()
{
    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Test");
    db.setUserName("bea");
    db.setPassword("bea");

    if (db.open())
        test=true;

    return test;
}
