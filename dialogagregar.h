#ifndef DIALOGAGREGAR_H
#define DIALOGAGREGAR_H

#include <QDialog>
#include <QLineEdit>

#include "header.h"
#include "campo.h"
namespace Ui {
class DialogAgregar;
}

class DialogAgregar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAgregar(QString path, QWidget *parent = 0);
    ~DialogAgregar();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    QString path;
    Header *header;
    Ui::DialogAgregar *ui;
    QList<QLineEdit*> lines;
    QLineEdit *crearLine(Campo* campo);
    bool append_registro(QString registro, int availlist);
    bool rewrite_registro(QString registro, int availlist);
};

#endif // DIALOGAGREGAR_H
