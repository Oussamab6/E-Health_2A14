#ifndef GESTIONDEPATIENT_H
#define GESTIONDEPATIENT_H
#include"patient.h"
#include <QWidget>
#include<QDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
class gestiondepatient;
}
QT_END_NAMESPACE

class gestiondepatient : public QDialog
{
   Q_OBJECT

public:
   explicit gestiondepatient(QWidget *parent = nullptr);
   ~gestiondepatient();
private slots:
   void on_pushButton_5_clicked();
   void on_pushButton_clicked();

   void on_supprimer_clicked();

private:
   Ui::gestiondepatient *ui;

};

#endif // GESTIONDEPATIENT_H

