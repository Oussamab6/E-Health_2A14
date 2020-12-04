#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->cINLineEdit->setMaxLength(8);



    ui->tableView->setModel(tmpdonneur.afficher());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewDon->setModel(tmpdon.afficher());
    ui->tableViewDon->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDon->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


    int cin = ui->cINLineEdit->text().toInt();
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





void MainWindow::on_pushButton_6_clicked()
{
    if (ui->pushButton_6->isChecked())
    {
        ui->pushButton_6->setDisabled(true);
        ui->pushButton_6->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("DONNEUR");
        tableModel->select();
        ui->tableView->setModel(tableModel);
        ui->pushButton_6->setDisabled(false);
    }
    else
    {
        ui->pushButton_6->setText("Modifier");
        ui->tableView->setModel(tmpdonneur.afficher());


    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();

    int cin =select->selectedRows(0).value(0).data().toInt();

    if(tmpdonneur.supprimer(cin))
    {
        ui->tableView->setModel(tmpdonneur.afficher());
        ui->statusbar->showMessage("Donneur supprimé");
    }

}

void MainWindow::on_pushButton_4_clicked()
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

void MainWindow::on_pushButton_7_clicked()
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

//don fonctions
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

void MainWindow::on_pushButton_3_clicked()
{
    QString input=ui->lineEditRdonneur->text();
    if (ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherNom(input));
    else if (!ui->checkBox_nom->isChecked() && ui->checkBox_type->isChecked() && !ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherGroupeS(input));
    else if (!ui->checkBox_nom->isChecked() && !ui->checkBox_type->isChecked() && ui->checkBox_date->isChecked())
        ui->tableView->setModel(tmpdonneur.rechercherDate(input));
}
