#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "reservation.h"
#include "statistique.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include"QDate"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_ajouter_clicked()
{
       int id_r = ui->id_r->text().toInt();
       QString nom_pat = ui->nom_pat->text();
       QString prenom_pat = ui->prenom_pat->text();
       QString email_pat = ui->email_pat->text();
       QString date_r = ui->date_r->text();
       QString sexe_e = ui->sex_e->text();


       reservation e (id_r,nom_pat,prenom_pat,email_pat,date_r,sexe_e);
         bool test=e.ajouter(id_r,nom_pat,prenom_pat,email_pat,date_r,sexe_e);
         if(test)
       {ui->tabreservation_2->setModel(tmpres.afficher());//refresh
       QMessageBox::information(nullptr, QObject::tr("Ajouter une reservation"),
                         QObject::tr("reservation ajouté.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

       }
         else
             QMessageBox::critical(nullptr, QObject::tr("Ajouter un emploi du temps"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow2::on_supprimer_clicked()
{
    int id = ui->reference_sup_e->text().toInt();
    bool test=tmpres.supprimer(id);
    if(test)
    {ui->tabreservation_2->setModel(tmpres.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer Reservation "),
                    QObject::tr("Reservation supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow2::on_modifier_clicked()
{
    int id_r = ui->id_r->text().toInt();
    QString nom_pat = ui->nom_pat->text();
    QString prenom_pat = ui->prenom_pat->text();
    QString email_pat = ui->email_pat->text();
    QString date_r = ui->date_r->text();
    QString sexe_e = ui->sex_e->text();
    reservation E;
    bool test=false;
    { if((sexe_e!="H")||(sexe_e!="F"))
            test=true;}
     if(test)E.modifier(id_r,nom_pat,prenom_pat,email_pat,date_r,sexe_e);
    if(test)
  {ui->tabreservation_2->setModel(tmpres.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Ajouter une reservation"),
                    QObject::tr("RESERVATION ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une reservation"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
}

void MainWindow2::on_chercher_employe_clicked()
{
    int id = ui->chercher_e->text().toInt();
            ui->afficher_trie->setModel(tmpres.recherche_e(id));
}

void MainWindow2::on_imprimer_res_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->afficher_trie->model()->rowCount();
            const int columnCount = ui->afficher_trie->model()->columnCount();
            QString TT = QDate::currentDate().toString("yyyy/MM/dd");
            out <<"<html>\n"
                  "<head>\n"
                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                << "<title>ERP - COMmANDE LIST<title>\n "
                << "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<h1 style=\"text-align: center;\"><strong> *****LISTE DES Factures ***** "+TT+"</strong></h1>"
                "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                  "</br> </br>";
            // headers
            out << "<thead><tr bgcolor=#d6e5ff>";
            for (int column = 0; column < columnCount; column++)
                if (!ui->afficher_trie->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->afficher_trie->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->afficher_trie->isColumnHidden(column)) {
                        QString data =ui->afficher_trie->model()->data(ui->afficher_trie->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *baba = new QPrintDialog(&printer, NULL);
            if (baba->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
}

void MainWindow2::on_tri_asc_res_clicked()
{
      ui->tabreservation_2->setModel(tmpres.tri(1));
}

void MainWindow2::on_tri_desc_res_clicked()
{
    ui->tabreservation_2->setModel(tmpres.tri(0));
}

void MainWindow2::on_statistiques_clicked()
{
    Statistique *a=new Statistique();
    a->show();
}
