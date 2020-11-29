#ifndef AFFICHER_H
#define AFFICHER_H

#include <QDialog>

namespace Ui {
class afficher;
}

class afficher : public QDialog
{
    Q_OBJECT

public:
    explicit afficher(QWidget *parent = nullptr);
    ~afficher();

private:
    Ui::afficher *ui ;
};

#endif // AFFICHER_H
