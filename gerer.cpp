#include "gerer.h"
#include "ui_gerer.h"
#include<QString>
#include<QThread>
#include <QMessageBox>
#include "EMPLOYE.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include<QtPrintSupport/QPrinter>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>





Gerer::Gerer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gerer)
{
    ui->setupUi(this);
    EMPLOYE e;
    ui->tableView_em->setModel(e.afficher());
    //l'animation pour "Bienvenue"
    animation= new QPropertyAnimation(ui->label_7, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(ui->label_7->geometry());
    animation->setEndValue(QRect(200,100,300,100));
    animation->start();

    //l'animation pour "choisir votre choix SVP"
    animation= new QPropertyAnimation(ui->label_11, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(ui->label_11->geometry());
    animation->setEndValue(QRect(150,200,350,150));
    animation->start();
    MainWindow M ;


}

Gerer::~Gerer()
{
    delete ui;
}


void Gerer::on_pushButton_ajouter_clicked()
{
    int cin=ui->lineEditCin->text().toInt();
    QString nom=ui->lineEditNom->text();
    QString prenom=ui->lineEditPrenom->text();
    QString mail=ui->lineEditMail->text();
    QString DDN =ui->dateEdit->text() ;
    QString Tache =ui->comboBox_Tache->currentText();

 EMPLOYE e (cin,nom,prenom,mail,DDN,Tache);
 bool test=e.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView_em->setModel(e.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}
void Gerer::on_pushButton_mod_clicked()
{
        int cin = ui->lineEditCin_2->text().toInt() ;
        QString nom= ui->lineEditNom_2->text();
        QString prenom=ui->lineEditPrenom_2->text();
        QString mail=ui->lineEditMail_2->text();
        QString DDN=ui->dateEdit_2->text() ;
        QString Tache=ui->comboBox_Tache2->currentText() ;

       EMPLOYE e (cin,nom,prenom,mail,DDN,Tache);
       bool test=e.modifier();
        QMessageBox msgBox;
        if(test)
          {  msgBox.setText("Modifier avec succes.");
            ui->tableView_em->setModel(e.afficher());
        }
        else
            msgBox.setText("Echec de modification");
            msgBox.exec();



}
void Gerer::on_pushButton_sup_clicked()
{

   int x =ui->lineEdit_supp->text().toInt();
    bool test=ee.supprimer(x);
    QMessageBox msgBox;

    if(test)
       {
    msgBox.setText("Suppression avec succes.");
    ui->tableView_em->setModel(ee.afficher());//refreche

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();


}




void Gerer::on_tableView_em_activated(const QModelIndex &index)
{   EMPLOYE ee;
    QString val = ui->tableView_em->model()->data(index).toString();
    QString cin_string= QString::number(ee.get_cin());

    QSqlQuery query;
     query.prepare("select * from employe where cin =:val or nom =:val or prenom=:val or mail=:val or DDN=:val or Tache=:val  ");
     query.bindValue(":val", val);

    if (query.exec())
    {
        while (query.next())
        {
            ui->lineEditCin_2->setText(query.value(0).toString());
            ui->lineEditNom_2->setText(query.value(1).toString());
            ui->lineEditPrenom_2->setText(query.value(2).toString());
            ui->lineEditMail_2->setText(query.value(3).toString());
            ui->dateEdit_2->setDate(query.value(4).toDate());
            ui->comboBox_Tache2->setCurrentText(query.value(5).toString());
        }
    }
    else
    {
        QMessageBox::critical(this ,tr("error::"),query.lastError().text());
    }

}



void Gerer::on_pushButton_2_clicked()
{
   /* MainWindow M ;
    M.exec();*/

}


void Gerer::on_pushButton_refreche_clicked()
{
    EMPLOYE e ;
    ui->tableView_em->setModel(e.afficher());

}


void Gerer::on_comboBox_trier_activated(const QString &arg1)
{
    EMPLOYE ee;
   QSqlQueryModel * modal = new QSqlQueryModel();
   QSqlQuery * qry = new QSqlQuery();
   if (arg1=="DDN et nom et cin")
   {
    qry->prepare("Select * from employe order by DDN ,cin,nom ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_em->setModel(modal);
    ui->tableView_em->show();
   }
  else if (arg1=="nom")
   {
    qry->prepare("Select * from employe order by nom desc");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_em->setModel(modal);
    ui->tableView_em->show();
   }

   else if (arg1=="prenom")
   {
    qry->prepare("Select * from employe order by prenom ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_em->setModel(modal);
    ui->tableView_em->show();
   }

}
void Gerer::on_comboBox_chercher_activated(const QString &arg1)
{
    EMPLOYE ee;
    if(arg1=="cin et nom et prenom ")
    {
    ee.chercher(ui->lineEditCin_2->text().toInt(),ui->lineEditNom_2->text(),ui->lineEditPrenom_2->text());
    ui->tableView_em->setModel(ee.afficher_unemploye());
    }
    else if (arg1=="cin")
    {
        ee.chercher_cin(ui->lineEditCin_2->text().toInt());
        ui->tableView_em->setModel(ee.afficher_unemploye_cin());

    }
    else if (arg1=="nom et prenom")
    {
        ee.chercher_nom_prenom(ui->lineEditNom_2->text(),ui->lineEditPrenom_2->text());
        ui->tableView_em->setModel(ee.afficher_unemploye_nom_prenom());

    }
}

void Gerer::on_pushButton_pdf_clicked()
{

        QString strStream;
        QTextStream out(&strStream);

         const int rowCount = ui->tableView_em->model()->rowCount();
         const int columnCount = ui->tableView_em->model()->columnCount();
        out <<  "<html>\n"
        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des employes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView_em->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView_em->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_em->isColumnHidden(column)) {
                                 QString data = ui->tableView_em->model()->data(ui->tableView_em->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);


}

void Gerer::on_pushButton_imprimer_clicked()
{
        QPrinter printer;

        printer.setPrinterName("desiered printer name");

      QPrintDialog dialog(&printer,this);

        if(dialog.exec()== QDialog::Rejected)

            return;
}



