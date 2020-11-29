#ifndef GESIONDEDM_H
#define GESIONDEDM_H

#include <QDialog>

namespace Ui {
class gesiondedm;
}

class gesiondedm : public QDialog
{
    Q_OBJECT

public:
    explicit gesiondedm(QWidget *parent = nullptr);
    ~gesiondedm();
private slots:
    void on_pushButton_clicked();

   // Void on_groupBox_clicked(bool checked);

  // void on_listView_indexesMoved(const QModelIndexList &indexes);

private:
    Ui::gesiondedm *ui;
};

#endif // GESIONDEDM_H
