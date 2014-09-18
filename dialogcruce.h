#ifndef DIALOGCRUCE_H
#define DIALOGCRUCE_H

#include <QDialog>
#include "header.h"
namespace Ui {
class DialogCruce;
}

class DialogCruce : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCruce(QWidget *parent = 0);
    ~DialogCruce();

private slots:
    void on_pb_llenar_tabla_clicked();

    void on_pb_tabla1_clicked();

    void on_pb_tabla1_2_clicked();

private:
    Header *principal;
    Header *secundario;
    Ui::DialogCruce *ui;
};

#endif // DIALOGCRUCE_H
