#ifndef GESTION_DE_PATION_H
#define GESTION_DE_PATION_H
#include"patient.h"
#include <QWidget>
#include <QDialog>

namespace Ui {
class Gestion_de_pation;
}

class Gestion_de_pation : public QDialog
{
    Q_OBJECT

public:
    explicit Gestion_de_pation(QWidget *parent = nullptr);
    ~Gestion_de_pation();
private slots:
   void on_pushButton_5_clicked();
   void on_pushButton_clicked();

   void on_supprimer_clicked();

private:
    Ui::Gestion_de_pation *ui;
};

#endif // GESTION_DE_PATION_H
