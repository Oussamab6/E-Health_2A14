#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"liste.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player=new QMediaPlayer(this);


    animation= new QPropertyAnimation(ui->label_2, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(ui->label_2->geometry());
    animation->setEndValue(QRect(450,50,200,200));
    animation->start();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: on_pushButton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:\\Users\\Synda\\OneDrive\\Bureau\\patient\\click-sound.mp3"));
    player->play();
    qDebug()<<player->errorString();
    liste l;
    l.exec();
}

