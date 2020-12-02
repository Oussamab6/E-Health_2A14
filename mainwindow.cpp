#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    song= new QMediaPlayer(this);
        img= new QPropertyAnimation(ui->label_4, "geometry");
        img->setDuration(3000);
        img->setStartValue(ui->label_4->geometry());
        img->setEndValue(QRect(450,50,200,200));
        img->start();
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
   song->setMedia(QUrl::fromLocalFile("C:\\Users\\asus\\Desktop\\projet\\sound1.mp3"));
    song->play();
    qDebug()<<song->errorString();
    Form f;
    f.exec();
}
