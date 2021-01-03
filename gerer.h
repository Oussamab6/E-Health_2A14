#ifndef GERER_H
#define GERER_H
#include<QThread>
#include <QWidget>
#include <QDialog>
#include<QPropertyAnimation>
#include "EMPLOYE.h"
#include "tache.h"
#include "arduino.h"




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

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_font_clicked();

private:
    Ui::Gerer *ui;
    QPropertyAnimation* animation ;
    EMPLOYE ee;
    tache t ;
    QByteArray data;
    arduino A;
};

#endif // GERER_H
