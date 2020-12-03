#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emploi_du_temps.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include"QDate"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_emp_clicked()
{     int id_res = ui->id_res->text().toInt();
      int id_doc = ui->id_res->text().toInt();
    QString email_doc = ui->email_doc->text();
      QString date_rv = ui->date_rv->text();
        int heure_rv = ui->heure_rv->text().toInt();

    emploi e (id_res,id_doc,email_doc,date_rv,heure_rv);
      bool test=e.ajouter(id_res,id_doc,email_doc,date_rv,heure_rv);
      if(test)
    {ui->tabemploi_2->setModel(tmpemp.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un emploi du temps"),
                      QObject::tr("Emploi du temps ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un emploi du temps"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


    }


void MainWindow::on_supprimer_emploi_clicked()
{
    int id = ui->reference_sup_e->text().toInt();
    bool test=tmpemp.supprimer(id);
    if(test)
    {ui->tabemploi_2->setModel(tmpemp.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer l'emploi"),
                    QObject::tr("EMPLOI supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
}

void MainWindow::on_modifier_emp_clicked()
{
    int id_res = ui->id_res->text().toInt();
         int id_doc = ui->id_res->text().toInt();
       QString email_doc = ui->email_doc->text();
         QString date_rv = ui->date_rv->text();
           int heure_rv = ui->heure_rv->text().toInt();
    emploi E;
    bool test=false;
    { if((heure_rv<0)||(heure_rv))
            test=true;}
     if(test)E.modifier(id_res,id_doc,email_doc,date_rv,heure_rv);
    if(test)
  {ui->tabemploi_2->setModel(tmpemp.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Ajouter un emploi du temps"),
                    QObject::tr("EMPLOI ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un emploi du temps"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
}

void MainWindow::on_chercher_emploi_clicked()
{
    int id = ui->chercher_id->text().toInt();
            ui->afficher_emp->setModel(tmpemp.recherche_e(id));
}

void MainWindow::on_imprimer_emploi_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->afficher_emp->model()->rowCount();
            const int columnCount = ui->afficher_emp->model()->columnCount();
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
                if (!ui->afficher_emp->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->afficher_emp->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->afficher_emp->isColumnHidden(column)) {
                        QString data =ui->afficher_emp->model()->data(ui->afficher_emp->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_trier_emploi_cr_clicked()
{
    ui->tabemploi_2->setModel(tmpemp.tri(1));
}

void MainWindow::on_trier_emploi_decr_clicked()
{
      ui->tabemploi_2->setModel(tmpemp.tri(0));
}
