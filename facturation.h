#ifndef FACTURATION_H
#define FACTURATION_H

#include <QWidget>
#include<QDialog>
namespace Ui {
class facturation;
}

class facturation : public QDialog
{
    Q_OBJECT

public:
    explicit facturation(QWidget *parent = nullptr);
    ~facturation();

private:
    Ui::facturation *ui;
};

#endif // FACTURATION_H
