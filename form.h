#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDialog>
#include "medicament.h"
#include <thread>
#include "machine.h"


namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_ajout_clicked();

    void on_pushButton_mod_clicked();

    void on_pushButton_supp_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_comboBox_trier_activated(const QString &arg1);

    void on_comboBox_reche_activated(const QString &arg1);

    void on_pushButton_ajouter2_clicked();

    void on_pushButton_mod_2_clicked();

    void on_pushButton_supp_2_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButton_refreche_2_clicked();

    void on_comboBox_trier_2_activated(const QString &arg1);

    void on_comboBox_reche_2_activated(const QString &arg1);

   // void on_pushButton_supp_5_clicked();

private:
    Ui::Form *ui;
    medicament m;
    machine e;

};

#endif // FORM_H
