#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "donneur.h"
#include "don.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QDebug>

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
   // void on_pushButton_clicked();

  //  void on_pushButton_6_clicked();

  //  void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButtonAjouterDon_clicked();

    void on_pushButtonModifierDon_clicked();

    void on_pushButtonSupprimerDon_clicked();

    void on_pushButtonImprimerDon_clicked();

    void on_pushButtonRechercheDon_clicked();

    void on_pushButtonTrierDon_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_statistique_clicked();

//    void on_Button_RechercheDonneur_clicked();

    void on_pushButton_AjouterDonneur_clicked();

    void on_pushButton_ModifierDonneur_clicked();

    void on_pushButton_SupprimerDonneur_clicked();

    void on_pushButton_RechercherDonneur_clicked();

    void on_pushButton_TrierDonneur_clicked();

    void on_pushButton_ImprimerDonneur_clicked();

private:
    Ui::MainWindow *ui;
    donneur tmpdonneur;
    don tmpdon;
};
#endif // MAINWINDOW_H
