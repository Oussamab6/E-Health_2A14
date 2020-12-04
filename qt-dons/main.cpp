#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.createConnection();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                              QObject::tr("connection successful.\n"
                                          "Click Cancel to exit."), QMessageBox::Ok);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
