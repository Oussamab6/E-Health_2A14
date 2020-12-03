#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QDialog>
#include"connecion.h"
#include "qcustomplot.h"
#include <QWidget>

namespace Ui {
class statistiques;
}

class statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit statistiques(QWidget *parent = nullptr);
    ~statistiques();
    void makePolt();


private:
    Ui::statistiques *ui;
};

#endif // STATISTIQUES_H
