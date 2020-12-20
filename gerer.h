#ifndef GERER_H
#define GERER_H
#include<QThread>
#include <QWidget>
#include <QDialog>
#include<QPropertyAnimation>
#include "EMPLOYE.h"
#include "tache.h"
#include "arduino.h"
#include "patient.h"
#include "dossiermedical.h"



namespace Ui {
class Gerer;
}

class Gerer : public QDialog
{
    Q_OBJECT

public:
    explicit Gerer(QWidget *parent = nullptr);
    void sleep(int s) { QThread::sleep(s); }
    ~Gerer();
private slots:
    void detction_de_chaleur();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_sup_clicked();
    void on_tableView_em_activated(const QModelIndex &index);
    void on_pushButton_mod_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_trier_activated(const QString &arg1);
    void on_comboBox_chercher_activated(const QString &arg1);
    void on_pushButton_pdf_clicked();
    void on_pushButton_imprimer_clicked();
    void on_pushButton_refreche_clicked();


    void on_pushButton_ajouter_Tache_clicked();

    void on_pushButton_mod_2_clicked();

    void on_pushButton_sup_2_clicked();

    void on_tableView_em_2_activated(const QModelIndex &index);

    void on_pushButton_refreche_2_clicked();

    void on_comboBox_trier_2_activated(const QString &arg1);

    void on_comboBox_chercher_2_activated(const QString &arg1);

    void on_pushButton_pdf_2_clicked();

    void on_pushButton_imprimer_2_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);



    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_MODIFIER_clicked();

    void on_tab_patient_2_activated(const QModelIndex &index);

    void on_pushButton_supp_clicked();

    void on_REFRESH_clicked();

    void on_comboBox_trier_3_activated(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_ajouter_2_clicked();

    void on_pushButton_mod_4_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_table_dossier_activated(const QModelIndex &index);

    void on_facturation_2_clicked();
    int somme();


    void on_imprimer_2_clicked();

private:
    Ui::Gerer *ui;
    QPropertyAnimation* animation ;
     patient p;
     dossiermedical d;
    EMPLOYE ee;
    tache t ;
    QByteArray data;
    arduino A;
};

#endif // GERER_H
