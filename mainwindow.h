#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"patient.h"

#include <QMainWindow>
#include<QPropertyAnimation>
#include<QtMultimedia/QMediaPlayer>
#include<QDebug>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation* animation;
    QMediaPlayer* player ;

};
#endif // MAINWINDOW_H
