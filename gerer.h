#ifndef GERER_H
#define GERER_H
#include<QThread>
#include <QWidget>
#include <QDialog>
#include<QPropertyAnimation>
#include "EMPLOYE.h"



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


private:
    Ui::Gerer *ui;
    QPropertyAnimation* animation ;
    EMPLOYE ee;
};

#endif // GERER_H