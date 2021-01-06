#ifndef HEALTH_H
#define HEALTH_H

#include<QThread>
#include <QWidget>
#include <QDialog>
#include<QPropertyAnimation>
#include "EMPLOYE.h"
#include "tache.h"
#include "arduino.h"
#include "patient.h"
#include "dossiermedical.h"
#include "medicaments.h"
#include "machines.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include "donneur.h"
#include "don.h"

namespace Ui {
class health;
}

class health : public QDialog
{
    Q_OBJECT

public:
    explicit health(QWidget *parent = nullptr);
    void sleep(int s) { QThread::sleep(s); }
    ~health();
    void afficher();
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



    void on_pushButton_alll_clicked();

    void on_pushButton_desaL_clicked();

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




    void on_pushButton_ajout_clicked();

    void on_pushButton_mod_3_clicked();

    void on_pushButton_supp_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_R_clicked();

    void on_comboBox_trier_4_activated(const QString &arg1);

    void on_comboBox_reche_activated(const QString &arg1);

    void on_pushButton_ajouter2_clicked();

    void on_pushButton_mod_9_clicked();

    void on_pushButton_supp_5_clicked();

    void on_tableView_3_activated(const QModelIndex &index);

    void on_pushButton_refreche_5_clicked();

    void on_comboBox_trier_9_activated(const QString &arg1);

    void on_comboBox_reche_3_activated(const QString &arg1);

    void on_pushButton_AjouterDonneur_2_clicked();

    void on_pushButton_ModifierDonneur_2_clicked();

    void on_pushButton_SupprimerDonneur_2_clicked();

    void on_pushButton_ImprimerDonneur_2_clicked();

    void on_pushButton_RechercherDonneur_2_clicked();

    void on_pushButton_TrierDonneur_2_clicked();

    void on_pushButton_statistique_2_clicked();

    void on_pushButtonAjouterDon_2_clicked();

    void on_pushButtonModifierDon_2_clicked();

    void on_pushButtonSupprimerDon_2_clicked();

    void on_pushButtonImprimerDon_2_clicked();

    void on_pushButtonRechercheDon_2_clicked();

    void on_pushButtonTrierDon_2_clicked();

    /********************************************************************************************/
    void on_pushButton_gc_clicked();

    void on_pushButton_2_gc_clicked();

    void on_pushButton_14_gc_clicked();

    void on_pushButton_15_gc_clicked();

    void on_pushButton_7_gc_clicked();

    void on_tableView_gc_clicked(const QModelIndex &index);

    void on_pushButton_8_gc_clicked();

    void on_pushButton_9_gc_clicked();

    void on_pushButton_16_gc_clicked();

    void on_pushButton_6_gc_clicked();

    void on_pushButton_18_gc_clicked();
    void makePlot_remise ();
        QVector<double> Statistique_remise();
        void on_pushButton_17_gc_clicked();

        void on_pushButton_19_gc_clicked();

        void on_pushButton_3_gc_clicked();

        void on_tableView_2_gc_clicked(const QModelIndex &index);

        void on_pushButton_4_gc_clicked();

        void on_pushButton_11_gc_clicked();

        void on_pushButton_10_gc_clicked();

        void on_pushButton_12_gc_clicked();

        void on_pushButton_5_gc_clicked();

        void on_pushButton_20_gc_clicked();
        void uglyPrint2(QPrinter *printer);


        void on_pushButton_em_clicked();
        void on_pushButton_ta_clicked();
        void on_pushButton_don_clicked();
        void on_pushButton_pa_clicked();
        void on_pushButton_dm_clicked();
        void on_pushButton_md_clicked();
        void on_pushButton_ma_clicked();
        void on_pushButton_pc_clicked();


        void on_pushButton_fa_clicked();

        void on_pushButton_ret1_clicked();
        void on_pushButton_ret2_clicked();
        void on_pushButton_ret3_clicked();
        void on_pushButton_ret4_clicked();
        void on_pushButton_ret5_clicked();
        void on_pushButton_ret6_clicked();
        void on_pushButton_ret7_clicked();
        void on_pushButton_ret8_clicked();
        void on_pushButton_ret9_clicked();
        void on_pushButton_ret10_clicked();


        void on_pushButton_ret11_clicked();

        void on_pushButton_arduino_clicked();

private:
    Ui::health *ui;
    QPropertyAnimation* animation ;
     patient p;
     dossiermedical d;
    EMPLOYE ee;
    tache t ;
    QByteArray data;
    arduino A;
    medicament m;
    machine e;
    donneur tmpdonneur;
    don tmpdon;
    QSqlTableModel *model;
};

#endif // HEALTH_H