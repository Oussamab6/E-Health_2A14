#ifndef LOGIN_H
#define LOGIN_H
#include<QDebug>
#include<QFileInfo>
#include "EMPLOYE.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login;}
QT_END_NAMESPACE
class login: public QMainWindow

{
        Q_OBJECT
public:
    login(QWidget *parent = nullptr);
    ~login();
private slots :
    void on_pushButton_log_clicked();
private :
    Ui::login *Ui ;
    QSqlDatabase test_bd;

};

#endif // LOGIN_H
