#ifndef SALLEDATTENTE_H
#define SALLEDATTENTE_H

#include <QWidget>
#include<QDialog>

namespace Ui {
class salledattente;
}

class salledattente : public QDialog
{
    Q_OBJECT

public:
    explicit salledattente(QWidget *parent = nullptr);
    ~salledattente();

private:
    Ui::salledattente *ui;
};

#endif // SALLEDATTENTE_H
