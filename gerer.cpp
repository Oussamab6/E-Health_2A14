#include "gerer.h"
#include "ui_gerer.h"
#include<QString>
#include<QThread>
#include <QMessageBox>
#include "EMPLOYE.h"
#include "tache.h"
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
#include <QFontDialog>
//#include "arduinoo.h"
//#include "arduino_final.h"
#include "calculatrice.h"
#include "ui_calculatrice.h"




Gerer::Gerer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gerer)
{
    ui->setupUi(this);
   //**********************************************************
   int ret =A.connect_arduino();//lancer la connection to arduino
    switch (ret) {

    case(0):qDebug()<<"arduino is available and connect to : "<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available and not  connect to : "<<A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available ";
        break;

    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(detction_de_chaleur()));


    //*****************************************************************
    EMPLOYE e;
    ui->tableView_em->setModel(e.afficher());
    ui->tableView_em_2->setModel(t.afficher_tache());

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
    QString cinc=QString::number(cin);
if(cinc.size()==8)
{
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
else{
    QMessageBox msgBox;
    msgBox.setText("Entrer 8 chiffres pour le CIN SVP");
    msgBox.exec();}
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

   int x =ui->lineEditCin_2->text().toInt();
    bool test=ee.supprimer(x);
    QMessageBox msgBox;

    if(test)
       {
    msgBox.setText("Suppression avec succes.");
    ui->tableView_em->setModel(ee.afficher());//refreche

    }
    else
       { msgBox.setText("Echec de suppression");
        msgBox.exec();
       }

}



void Gerer::on_tableView_em_activated(const QModelIndex &index)
{   EMPLOYE ee;
    QString val = ui->tableView_em->model()->data(index).toString();
    int x = ui->tableView_em->model()->data(index).toString().toInt();

    QString cin_string= QString::number(ee.get_cin());

    QSqlQuery query;
     query.prepare("select * from employe where cin =:x or nom =:val or prenom=:val or mail=:val or DDN=:val or Tache=:val  ");
     query.bindValue(":val", val);
     query.bindValue(":x",x);

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
   if (arg1=="cin et nom et prenom")
   {
    qry->prepare("Select * from employe order by cin,nom,prenom ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_em->setModel(modal);
    ui->tableView_em->show();
   }
  else if (arg1=="nom")
   {
    qry->prepare("Select * from employe order by nom");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_em->setModel(modal);
    ui->tableView_em->show();
   }

   else if (arg1=="prenom")
   {
    qry->prepare("Select * from employe order by prenom desc");
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


//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************

void Gerer::on_pushButton_refreche_2_clicked()
{
    tache t;
        ui->tableView_em_2->setModel(t.afficher_tache());
}

void Gerer::on_pushButton_ajouter_Tache_clicked()
{
    QString type_tache=ui->comboBox_type_tache->currentText();
    int salaire=ui->lineEdit_salaire->text().toInt();
    QString date_debut=ui->dateEdit_debut->text();
    QString date_fin=ui->dateEdit_fin->text();
    tache t(type_tache,salaire,date_debut,date_fin);
    bool test=t.ajouter_tache();
    QMessageBox msgBox;
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("AJOUTER"),
                    QObject::tr("AJOUT SUCCES.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_em_2->setModel(t.afficher_tache());
    }
    else {QMessageBox::information(nullptr, QObject::tr("AJOUTER"),
                                   QObject::tr("ECHEC D'AJOUT.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);}

}
void Gerer::on_pushButton_mod_2_clicked()
{
    QString type_tache=ui->comboBox_type_tache_2->currentText();
    int salaire=ui->lineEdit_salaire_2->text().toInt();
    QString date_debut=ui->dateEdit_debut_2->text();
    QString date_fin=ui->dateEdit_fin_2->text();
    tache t(type_tache,salaire,date_debut,date_fin);
    bool test=t.modifier_tache();
    QMessageBox msgBox;
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("AJOUTER"),
                    QObject::tr("MODIFICATION SUCCES.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_em_2->setModel(t.afficher_tache());
    }
    else {QMessageBox::information(nullptr, QObject::tr("AJOUTER"),
                                   QObject::tr("ECHEC MODIFICATION.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);}

}

void Gerer::on_pushButton_sup_2_clicked()
{
    QString x=ui->comboBox_type_tache_2->currentText();
    bool test=t.supprimer_tache(x);
    QMessageBox msgBox;

    if(test)
       {
    msgBox.setText("Suppression avec succes.");
    ui->tableView_em_2->setModel(t.afficher_tache());//refreche

    }
    else
       { msgBox.setText("Echec de suppression");
        msgBox.exec();}
}
void Gerer::on_tableView_em_2_activated(const QModelIndex &index)
{
    tache t;
    QString val = ui->tableView_em_2->model()->data(index).toString();
    QString salaire_string= QString::number(t.get_salaire());
    QSqlQuery query;
    query.prepare(("select * from tache where type_tache=:val or salaire=:val or date_debut=:val or date_fin=:val  "));
    query.bindValue(":val", val);
    if (query.exec())
    {
        while (query.next())
        {
            ui->comboBox_type_tache_2->setCurrentText(query.value(0).toString());
            ui->lineEdit_salaire_2->setText(query.value(1).toString());
            ui->dateEdit_debut_2->setDate(query.value(2).toDate());
            ui->dateEdit_fin_2->setDate(query.value(3).toDate());
        }
    }
    else
    {
        QMessageBox::critical(this ,tr("error::"),query.lastError().text());
    }
}
void Gerer::on_comboBox_trier_2_activated(const QString &arg1)
{
    tache t;
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery * qry = new QSqlQuery();
    if (arg1=="DATE_DEBUT")
    {
        qry->prepare("Select * from tache order by date_debut ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_em_2->setModel(modal);
        ui->tableView_em_2->show();
    }
    else if (arg1=="DATE_FIN")
    {
        qry->prepare("Select * from tache order by date_fin ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_em_2->setModel(modal);
        ui->tableView_em_2->show();
    }
    else if (arg1=="SALAIRE ET DATE_DEBUT ET DATE_FIN")
    {
        qry->prepare("Select * from tache order by salaire,date_debut,date_fin ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_em_2->setModel(modal);
        ui->tableView_em_2->show();
    }
}
void Gerer::on_comboBox_chercher_2_activated(const QString &arg1)
{
    tache t ;
    if (arg1=="salaire")
    {
        t.chercher_tache_salaire(ui->lineEdit_salaire_2->text().toInt());
        ui->tableView_em_2->setModel(t.afficher_tache_salaire());
    }
    else if (arg1=="date_debut_type_salaire")
    {
        t.chercher_date_debut_type_salaire(ui->dateEdit_debut_2->text(),ui->comboBox_type_tache_2->currentText(),ui->lineEdit_salaire_2->text().toInt());
        ui->tableView_em_2->setModel(t.afficher_date_debut_type_salaire());
    }
    else if(arg1=="type")
    {
        t.chercher_type(ui->comboBox_type_tache_2->currentText());
        ui->tableView_em_2->setModel(t.afficher_type());
    }


}


void Gerer::on_pushButton_pdf_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

     const int rowCount = ui->tableView_em_2->model()->rowCount();
     const int columnCount = ui->tableView_em_2->model()->columnCount();
    out <<  "<html>\n"
    "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg("strTitle")
                     <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"

                    //     "<align='right'> " << datefich << "</align>"
                     "<center> <H1>Liste des Tache </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                 // headers
                 out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                 for (int column = 0; column < columnCount; column++)
                     if (!ui->tableView_em_2->isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(ui->tableView_em_2->model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 // data table
                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!ui->tableView_em_2->isColumnHidden(column)) {
                             QString data = ui->tableView_em_2->model()->data(ui->tableView_em_2->model()->index(row, column)).toString().simplified();
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

void Gerer::on_pushButton_imprimer_2_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

void Gerer::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{EMPLOYE ee;
    QString inputValue,filtrerChecked;
            inputValue=ui->lineEdit->text();
            ui->tableView_em->setModel(ee.rechercher_2(inputValue,"nom"));
}
void Gerer::detction_de_chaleur()
{
    data=A.read_from_arduino();
    if (data=="1")
    {
        QMessageBox::information(nullptr, QObject::tr("CHALEUR DETECTER"),
                    QObject::tr("UNE CHALEUR A ETE DETECTER .\n"
                                "SVP VOIR ARDUINO ."), QMessageBox::Cancel);
    }
    if (data=="4")

        ui->label_38->setText("LAMPE ALLUMER");//afficher on si les données reçues par arduino est 1

    else if(data=="5")

        ui->label_38->setText("LAMPE ETEINDRE");
}



void Gerer::on_pushButton_6_clicked()
{
    A.write_to_arduino("4");

}

void Gerer::on_pushButton_8_clicked()
{
    A.write_to_arduino("5");

}

void Gerer::on_pushButton_clicked()
{
    A.write_to_arduino("2");

}

void Gerer::on_pushButton_5_clicked()
{
    A.write_to_arduino("3");

}

void Gerer::on_font_clicked()
{
    bool ok ;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){

    } else {

    }
}

void Gerer::on_pushButton_9_clicked()
{
    calculatrice c ;
    c.exec();
}
