#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "reservation.h"
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include"QDate"
namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_chercher_employe_clicked();

    void on_imprimer_res_clicked();

    void on_tri_asc_res_clicked();

    void on_tri_desc_res_clicked();

    void on_statistiques_clicked();

private:
    Ui::MainWindow2 *ui;
    reservation tmpres;
};

#endif // MAINWINDOW2_H
