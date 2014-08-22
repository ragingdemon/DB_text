#ifndef DIALOGNUEVO_H
#define DIALOGNUEVO_H

#include <QDialog>
#include <vector>
#include "campo.h"
using std::vector;

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
    void on_pb_campo_clicked();

    void on_pb_archivo_clicked();

private:
    Ui::dialogNuevo *ui;
    vector<Campo*> campos;
};

#endif // DIALOGNUEVO_H
