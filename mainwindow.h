#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "emploi_du_temps.h"
#include <QMainWindow>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include"QDate"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_emp_clicked();

    void on_supprimer_emploi_clicked();

    void on_modifier_emp_clicked();

    void on_chercher_emploi_clicked();

    void on_imprimer_emploi_clicked();

    void on_trier_emploi_cr_clicked();

    void on_trier_emploi_decr_clicked();

private:
    emploi tmpemp;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
