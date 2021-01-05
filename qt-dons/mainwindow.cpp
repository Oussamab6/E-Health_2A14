#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextDocument>
#include <QDialog>
#include<QFileInfo>
#include<QFileDialog>
#include <QTextStream>
#include<QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //controle de saisie
    ui->setupUi(this);
    QValidator *validator_String=new QRegExpValidator(QRegExp("[A-Za-z ' ']+"),this);
    ui->cINLineEdit->setValidator(new QIntValidator(10000000,999999999,this));
    ui->cINLineEdit->setMaxLength(8);
    ui->referenceLineEdit->setValidator(new QIntValidator (10000000,999999999,this));
    ui->referenceLineEdit->setMaxLength(8);
    ui->quantiteLineEdit->setValidator(new QIntValidator(10000,99999,this));
    ui->nomLineEdit->setValidator(validator_String);
    ui->prenomLineEdit->setValidator(validator_String);
    QValidator *validator_Mail=new QRegExpValidator(QRegExp("[A-Za-z '@ ' '.']+"),this);
    ui->eMailLineEdit->setValidator(validator_Mail);


    ui->tableView->setModel(tmpdonneur.afficher());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewDon->setModel(tmpdon.afficher());
    ui->tableViewDon->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDon->setSelectionMode(QAbstractItemView::SingleSelection);
}

// Ajouter donneur
void MainWindow::on_pushButton_AjouterDonneur_clicked()
{
    QString cin = ui->cINLineEdit->text();
    QString nom= ui->nomLineEdit->text();
    QString prenom= ui->prenomLineEdit->text();
    QString email= ui->eMailLineEdit->text();
    QString sexe = ui->sexeComboBox->currentText();
    QString groupesanguin= ui->groupSanguinComboBox->currentText();
    QDate dateprelev= ui->dateDePrelevementDateEdit->date();



    donneur donneur(cin,nom,prenom,email,sexe,groupesanguin,dateprelev);

    bool test=donneur.ajouter();

    if (test)
        ui->tableView->setModel(tmpdonneur.afficher());


}

//Modifier Donneur
void MainWindow::on_pushButton_ModifierDonneur_clicked()
{
    if (ui->pushButton_ModifierDonneur->isChecked())
    {
        ui->pushButton_ModifierDonneur->setDisabled(true);
        ui->pushButton_ModifierDonneur->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("DONNEUR");
        tableModel->select();
        ui->tableView->setModel(tableModel);
        ui->pushButton_ModifierDonneur->setDisabled(false);
    }
    else
    {
        ui->pushButton_ModifierDonneur->setText("Modifier");
        ui->tableView->setModel(tmpdonneur.afficher());
    }
}


//Supprimer Donneur
void MainWindow::on_pushButton_SupprimerDonneur_clicked()
{

    QItemSelectionModel *select = ui->tableView->selectionModel();
    QMessageBox msgbox;
    int cin =select->selectedRows(0).value(0).data().toInt();
            msgbox.setWindowTitle("supprimer");
            msgbox.setText("voulez_vous supprimer cette réclamation?");
            msgbox.setStandardButtons(QMessageBox ::Yes);
            msgbox.addButton(QMessageBox::No);
            if(msgbox.exec()==QMessageBox::Yes)
{

    if(tmpdonneur.supprimer(cin))
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("suppression effectuée \n click cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(tmpdonneur.afficher());
        ui->statusbar->showMessage("Donneur supprimé");
    }

}
}

//imrpimer donneur
void MainWindow::on_pushButton_ImprimerDonneur_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("Title")
          <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

//Recherche Donneur
void MainWindow::on_pushButton_RechercherDonneur_clicked()
{
    QString input=ui->lineEditRdonneur->text();
    if (ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherNom(input));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherGroupeS(input));
    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherDate(input));
}


//Trier Donneur
void MainWindow::on_pushButton_TrierDonneur_clicked()
{


    if (ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("NOM",ui->comboBox->currentText()));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("GROUPE_SANGUIN",ui->comboBox->currentText()));
    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("DATE_PRELEV",ui->comboBox->currentText()));
    else if (ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("NOM,GROUPE_SANGUIN",ui->comboBox->currentText()));
    else if (ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("NOM,DATE_PRELEV",ui->comboBox->currentText()));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("GROUPE_SANGUIN,DATE_PRELEV",ui->comboBox->currentText()));
    else if (ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.trier("NOM,GROUPE_SANGUIN,DATE_PRELEV",ui->comboBox->currentText()));

}

// Ajouter Don
void MainWindow::on_pushButtonAjouterDon_clicked()
{
    int id=ui->referenceLineEdit->text().toInt();
    int quantite = ui->quantiteLineEdit->text().toInt();
    QString date_prelev=ui->dateDePrLVementDateEdit->date().toString("dd/MM/yyyy");
    QString emplacement=ui->emplacementLineEdit->text();

    don don(id,quantite,emplacement,date_prelev);

    bool test=don.ajouter();

    if (test)
    {
        ui->tableViewDon->setModel(tmpdon.afficher());
        ui->statusbar->showMessage("Don ajouté");
    }
}

//Modifier Don
void MainWindow::on_pushButtonModifierDon_clicked()
{
    if (ui->pushButtonModifierDon->isChecked())
    {
        ui->pushButtonModifierDon->setDisabled(true);
        ui->pushButtonModifierDon->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("DON");
        tableModel->select();
        ui->tableViewDon->setModel(tableModel);
        ui->pushButtonModifierDon->setDisabled(false);
    }
    else
    {
        ui->pushButtonModifierDon->setText("Modifier");
        ui->tableViewDon->setModel(tmpdon.afficher());

    }

}

//Supprimer Don
void MainWindow::on_pushButtonSupprimerDon_clicked()
{
    QItemSelectionModel *select = ui->tableViewDon->selectionModel();

    int id =select->selectedRows(0).value(0).data().toInt();

    if(tmpdon.supprimer(id))
    {
        ui->tableViewDon->setModel(tmpdon.afficher());
        ui->statusbar->showMessage("Don supprimé");
    }

}

//Imprimer Don
void MainWindow::on_pushButtonImprimerDon_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableViewDon->model()->rowCount();
    const int columnCount = ui->tableViewDon->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("Title")
          <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableViewDon->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableViewDon->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableViewDon->isColumnHidden(column)) {
                QString data = ui->tableViewDon->model()->data(ui->tableViewDon->model()->index(row, column)).toString().simplified();
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

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

//Recherche don
void MainWindow::on_pushButtonRechercheDon_clicked()
{
    QString recherche=ui->lineEditRechercheDon->text();
    if (ui->checkBoxRefDon->isChecked() && !ui->checkBoxQuantiteDon->isChecked() && !ui->checkBoxDateDon->isChecked())
    {
        int rechercheint=ui->lineEditRechercheDon->text().toInt();
        ui->tableViewDon->setModel(tmpdon.rechercherID(rechercheint));
    }
    else if (!ui->checkBoxRefDon->isChecked() && ui->checkBoxQuantiteDon->isChecked() && !ui->checkBoxDateDon->isChecked())
    {
        int rechercheint=ui->lineEditRechercheDon->text().toInt();
        ui->tableViewDon->setModel(tmpdon.rechercherQuantite(rechercheint));
    }
    else if (!ui->checkBoxRefDon->isChecked() && !ui->checkBoxQuantiteDon->isChecked() && ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.rechercherDate(recherche));
}

//Trier Don
void MainWindow::on_pushButtonTrierDon_clicked()
{
    if (ui->checkBoxRefDon->isChecked() && !ui->checkBoxQuantiteDon->isChecked() && !ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("ID_DON",ui->comboBoxDon->currentText()));
    else if (!ui->checkBoxRefDon->isChecked() && ui->checkBoxQuantiteDon->isChecked() && !ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("QUANTITE",ui->comboBoxDon->currentText()));
    else if (!ui->checkBoxRefDon->isChecked() && !ui->checkBoxQuantiteDon->isChecked() && ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("DATE_PRELEV",ui->comboBoxDon->currentText()));
    else if (ui->checkBoxRefDon->isChecked() && ui->checkBoxQuantiteDon->isChecked() && !ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("ID_DON,QUANTITE",ui->comboBoxDon->currentText()));
    else if (ui->checkBoxRefDon->isChecked() && !ui->checkBoxQuantiteDon->isChecked() && ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("ID_DON,DATE_PRELEV",ui->comboBoxDon->currentText()));
    else if (!ui->checkBoxRefDon->isChecked() && ui->checkBoxQuantiteDon->isChecked() && ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("QUANTITE,DATE_PRELEV",ui->comboBoxDon->currentText()));
    else if (ui->checkBoxRefDon->isChecked() && ui->checkBoxQuantiteDon->isChecked() && ui->checkBoxDateDon->isChecked())
        ui->tableViewDon->setModel(tmpdon.trier("ID_DON,QUANTITE,DATE_PRELEV",ui->comboBoxDon->currentText()));
}


void MainWindow::on_pushButton_statistique_clicked()
{
    float s;
    donneur d;
    s=d.stat1();
    ui->lab_stat1->setNum(s);
    float s1;
    s1=d.stat2();
    ui->lab_stat2->setNum(s1);
    float s2;
    s2=d.stat3();
    ui->lab_stat3->setNum(s2);
}



MainWindow::~MainWindow()
{
    delete ui;
}





