#ifndef LISTE_H
#define LISTE_H

#include <QDialog>

namespace Ui {
class liste;
}

class liste : public QDialog
{
    Q_OBJECT

public:
    explicit liste(QWidget *parent = nullptr);
    ~liste();
private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::liste *ui;
};

#endif // LISTE_H
