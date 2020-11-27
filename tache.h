#ifndef TACHE_H
#define TACHE_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class tache;
}

class tache : public QDialog
{
    Q_OBJECT

public:
    explicit tache(QWidget *parent = nullptr);
    ~tache();

private:
    Ui::tache *ui;
};

#endif // TACHE_H
