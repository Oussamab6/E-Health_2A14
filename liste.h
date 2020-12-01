#ifndef LISTE_H
#define LISTE_H
#include"patient.h"
#include <QWidget>
#include <QDialog>

namespace Ui {
class liste;
}

class liste : public QDialog
{
    Q_OBJECT

public:
    explicit liste(QWidget *parent = nullptr);
    ~liste();
private slots:
   void on_pushButton_clicked();
   void on_pushButton_MODIFIER_clicked();
   void on_pushButton_supp_clicked();
   void on_tab_patient_2_activated(const QModelIndex &index);

   void on_comboBox_trier_activated(const QString &arg1);

   void on_comboBox_activated(const QString &arg1);

   void on_pushButton_7_clicked();
 int somme();
private:
    Ui::liste *ui;
};

#endif // LISTE_H
