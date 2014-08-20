#ifndef DIALOGNUEVO_H
#define DIALOGNUEVO_H

#include <QDialog>

namespace Ui {
class dialogNuevo;
}

class dialogNuevo : public QDialog
{
    Q_OBJECT

public:
    explicit dialogNuevo(QWidget *parent = 0);
    ~dialogNuevo();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::dialogNuevo *ui;
};

#endif // DIALOGNUEVO_H
