#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDialog>
#include "medicament.h"
#include <thread>

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

private:
    Ui::Form *ui;
    medicament m;

};

#endif // FORM_H
