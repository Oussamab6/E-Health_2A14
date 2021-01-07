#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include"connection.h"
#include "qcustomplot.h"
#include <QWidget>
namespace Ui {
class Statistique;
}

class Statistique : public QDialog
{
    Q_OBJECT

public:
    explicit Statistique(QWidget *parent = nullptr);
    ~Statistique();
    void makePolt();

private:
    Ui::Statistique *ui;
};

#endif // STATISTIQUE_H
